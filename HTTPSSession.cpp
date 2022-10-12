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
#include <sstream>
#include <fstream>

#define BUFFER_SIZE 100000

void ctx_callback(const SSL *ssl, const char *line)
{
    std::ofstream file;
    file.open("log.key");
    file << line;
    file.close();
}

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
    SSL_CTX_set_keylog_callback(ctx, ctx_callback);
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
    HTTPMessage::headerMap headers;
    HTTPRequestMessage request(1.1, HTTPMethod::Get, path, headers);
    return this->send(request);
}

HTTPResponseMessage HTTPSSession::send(HTTPRequestMessage request)
{
    int rc;
    char buffer[BUFFER_SIZE];
    std::ostringstream input;
    memset(buffer, 0, sizeof(buffer));
    request.setHeader("HOST", this->host);
    request.setHeader("USER-AGENT", "Webcrawler/TS");
    if (!this->cookies.empty())
    {
        request.setHeader("Cookie", this->sendCookies());
    }

    std::string output = request.format();
    rc = SSL_write(ssl, output.c_str(), output.length());
    while (rc < output.length())
    {
        rc += SSL_write(ssl, (char *)output.c_str() + rc, output.length() - rc);
    }
    rc = 0;
    while (input.str().find("\r\n\r\n") == std::string::npos)
    {
        rc += SSL_read(ssl, buffer + rc, 1);
        input << buffer[rc - 1];
    }
    HTTPResponseMessage response(buffer);
    char *content = buffer + rc;
    if (response.getHeaders().count("Content-Length"))
    {
        rc = 0;
        while (rc < std::stoi(response.getHeaders().find("Content-Length")->second))
        {
            rc += SSL_read(ssl, content + rc, std::stoi(response.getHeaders().find("Content-Length")->second) - rc);
        }
    }
    std::string data(content);
    response.setData(data);
    this->updateSession(response);
    if (response.getStatus() == 302 || response.getStatus() == 301)
    {
        request.setPath(response.getHeaders().find("Location")->second);
        response = this->send(request);
    }

    return response;
}

void HTTPSSession::updateSession(HTTPResponseMessage response)
{
    for (auto &[key, value] : response.getHeaders())
    {
        if (key == "Set-Cookie")
        {
            this->setCookie(value);
        }
    }
}

void HTTPSSession::setCookie(std::string cookie)
{
    std::string key, value;
    int stringPointer;
    stringPointer = cookie.find("=");
    key = cookie.substr(0, stringPointer);
    cookie.erase(0, stringPointer + 1);
    stringPointer = cookie.find(";");
    value = cookie.substr(0, stringPointer);
    this->cookies[key] = value;
}

std::string HTTPSSession::sendCookies()
{
    std::ostringstream buffer;
    for (auto &[key, value] : this->cookies)
    {
        buffer << key << "=" << value << "; ";
    }
    std::string output = buffer.str();
    output.erase(output.rfind(";"));
    return output;
}

HTTPResponseMessage HTTPSSession::post(std::string path, std::string data, std::string type)
{
    HTTPMessage::headerMap headers;
    headers.insert(std::make_pair("Content-Length", std::to_string(data.length())));
    headers.insert(std::make_pair("Content-Type", type));
    HTTPRequestMessage request(1.1, HTTPMethod::Post, path, headers, data);
    return this->send(request);
}