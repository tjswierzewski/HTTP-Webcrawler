#ifndef HTTP_REQUEST_MESSAGE_H
#define HTTP_REQUEST_MESSAGE_H

#include "HTTPMessage.h"
#include "HTTPMethod.h"
#include <string>

class HTTPRequestMessage : public HTTPMessage
{
protected:
    HTTPMethod method;
    std::string path;

public:
    HTTPRequestMessage(float version, HTTPMethod method, std::string path, headerMap headers, std::string data = NULL);
    HTTPMethod getMethod();
    std::string getPath();
};

#endif