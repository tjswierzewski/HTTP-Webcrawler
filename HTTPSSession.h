#ifndef HTTPSSESSION_H
#define HTTPSSESSION_H

#include <map>
#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <HTMLMessage.h>

class HTTPSSession
{
private:
    typedef std::map<std::string, std::string> cookiesMap;
    cookiesMap cookies;
    int socket;
    const char *host, *port;
    bool https;
    SSL_CTX *ctx;
    SSL *ssl;

    int connectToHost();

    SSL_CTX *InitCTX(void);

public:
    HTTPSSession(const char *host, const char *port);
    ~HTTPSSession();
    HTTPResponseMessage get(std::string path, char *buffer, size_t bufferSize);
};
#endif