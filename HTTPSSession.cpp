#include "HTTPSSession.h"
#include "HTTPMessage.h"
#include "HTTPResponseMessage.h"
#include "HTTPRequestMessage.h"
#include "HTTPMethod.h"
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <iostream>

#define BUFFER_SIZE 10000

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

    sock = ::socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
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

HTTPResponseMessage HTTPSSession::get(std::string path)
{
    int rc;
    char buffer[BUFFER_SIZE];
    HTTPMessage::headerMap headers;
    headers["HOST"] = this->host;
    headers["USER-AGENT"] = "Webcrawler/TS";
    HTTPRequestMessage request(1.0, HTTPMethod::Get, path, headers);
    std::string output = request.format();
    SSL_write(ssl, output.c_str(), output.length());
    rc = SSL_read(ssl, buffer, BUFFER_SIZE);
    while (rc < BUFFER_SIZE && buffer[rc - 1] != '\n')
    {
        rc += SSL_read(ssl, buffer + rc, BUFFER_SIZE - rc);
    }
    return HTTPResponseMessage(buffer);
}