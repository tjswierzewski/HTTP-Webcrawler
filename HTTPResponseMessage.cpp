#include "HTTPResponseMessage.h"

HTTPResponseMessage::HTTPResponseMessage(std::string buffer) : HTTPMessage(buffer)
{
    while (buffer.find_first_of("\r\n") != 0)
    {
        int delim;
        delim = buffer.find_first_of(" ");
        this->version = std::stof(buffer.substr(4, delim));
        buffer.erase(0, delim);
        delim = buffer.find_first_of(" ");
        this->version = std::stoi(buffer.substr(0, delim));
        buffer.erase(0, delim);
    }
}

int HTTPResponseMessage::getStatus()
{
    return this->status;
}
std::string HTTPResponseMessage::getStatusMessage()
{
    return this->statusMessage;
}
