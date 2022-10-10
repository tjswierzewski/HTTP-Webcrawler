#include "HTTPMessage.h"
#include <string>
#include <iomanip>
#include <sstream>

HTTPMessage::HTTPMessage(std::string buffer)
{
    int delim = buffer.find_first_of("\r\n");
    buffer.erase(0, delim + 2);
    parseHeaders(&buffer);
    this->data = buffer;
}
HTTPMessage::HTTPMessage(headerMap headers, std::string data)
{
    this->headers = headers;
    this->data = data;
}
float HTTPMessage::getVersion()
{
    return this->version;
}
HTTPMessage::headerMap HTTPMessage::getHeaders()
{
    return this->headers;
}
std::string HTTPMessage::getData()
{
    return this->data;
}

void HTTPMessage::parseHeaders(std::string *buffer)
{
    std::string header, value;
    int delim, end;
    while (buffer->find_first_of("\r\n\r\n") != 0)
    {
        delim = buffer->find_first_of(':');
        header = buffer->substr(0, delim);
        buffer->erase(0, delim + 2);
        delim = buffer->find_first_of("\r\n");
        value = buffer->substr(0, delim);
        buffer->erase(0, delim + 2);
        this->headers[header] = value;
    }
    buffer->erase(0, 2);
}

std::string HTTPMessage::printVersion()
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(1) << this->version;
    return ss.str();
}