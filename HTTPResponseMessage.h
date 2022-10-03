#ifndef HTTP_RESPONSE_MESSAGE_H
#define HTTP_RESPONSE_MESSAGE_H

#include <string>
#include "HTTPMessage.h"

class HTTPResponseMessage : public HTTPMessage
{
protected:
    int status;
    std::string statusMessage;

public:
    HTTPResponseMessage(std::string buffer);
    ~HTTPResponseMessage();
    int getStatus();
    std::string getStatusMessage();
};

#endif