#ifndef HTTPSSESSION_H
#define HTTPSSESSION_H

#include <map>
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "HTTPResponseMessage.h"
#include "HTTPRequestMessage.h"

class HTTPSSession
{
public:
    typedef std::map<std::string, std::string> cookiesMap;

private:
    cookiesMap cookies;
    int socket;
    const char *host, *port;
    bool https;
    SSL_CTX *ctx;
    SSL *ssl;

    int connectToHost();
    SSL_CTX *InitCTX(void);
    HTTPResponseMessage send(HTTPRequestMessage);
    void updateSession(HTTPResponseMessage response);
    void setCookie(std::string value);

public:
    HTTPSSession(const char *host, const char *port);
    ~HTTPSSession();
    HTTPResponseMessage get(std::string);
};
#endif