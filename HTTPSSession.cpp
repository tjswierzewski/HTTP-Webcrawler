#include "HTTPSSession.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <iostream>

HTTPSSession::HTTPSSession(const char *host, const char *port)
{
    this->host = host;
    this->port = port;
    this->socket = connectToHost();
    if (this->socket < 0)
    {
        throw std::invalid_argument("Error in port creation");
    }
    SSL_library_init();
    this->ctx = InitCTX();
    this->ssl = SSL_new(ctx);
    SSL_set_fd(this->ssl, this->socket);
    if (SSL_connect(ssl) == -1)
    {
        ERR_print_errors_fp(stderr);
        throw std::invalid_argument("Error in SSL Connection");
    }
};

HTTPSSession::~HTTPSSession()
{
    SSL_free(this->ssl);
    SSL_CTX_free(this->ctx);
    close(this->socket);
}

int HTTPSSession::connectToHost()
{
    struct addrinfo hints, *addr;
    int sock, err;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    if ((err = getaddrinfo(this->host, this->port, &hints, &addr)) != 0)
    {
        std::cout << "Error" << err << ": " << gai_strerror(err) << std::endl;
        return -1;
    }

    sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (sock < 0)
    {
        perror("socket");
        return -1;
    }

    if (connect(sock, addr->ai_addr, addr->ai_addrlen) != 0)
    {
        perror("connect");
        return -1;
    }
    return sock;
}

SSL_CTX *HTTPSSession::InitCTX(void)
{
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    const SSL_METHOD *method = TLS_client_method();
    SSL_CTX *ctx = SSL_CTX_new(method);
    if (ctx == NULL)
    {
        ERR_print_errors_fp(stderr);
    }
    return ctx;
}

void HTTPSSession::get(std::string path, char *buffer, size_t bufferSize)
{
    int rc;
    std::string output;
    output.append("GET ");
    output.append(path);
    output.append(" HTTP/1.0\r\nHOST: ");
    output.append(this->host);
    output.append("\r\nUSER-AGENT: Webcrawler/TS\r\n\r\n");
    SSL_write(ssl, output.c_str(), output.length());
    rc = SSL_read(ssl, buffer, bufferSize);
    while (rc < bufferSize && buffer[rc - 1] != '\n')
    {
        rc += SSL_read(ssl, buffer + rc, bufferSize - rc);
    }
}