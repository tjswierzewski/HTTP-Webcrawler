#ifndef HTTP_REQUEST_MESSAGE_H
#define HTTP_REQUEST_MESSAGE_H

#include "HTTPMessage.h"
#include <string>

class HTTPRequestMessage : public HTTPMessage
{
protected:
    std::string method;
    std::string path;

public:
    HTTPRequestMessage(float version, std::string method, std::string path, HTTPMessage::headerMap headers, std::string data = "");
    std::string getMethod();
    std::string getPath();
    std::string format();
};

#endif