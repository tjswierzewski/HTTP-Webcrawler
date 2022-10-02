#include "HTTPRequestMessage.h"
#include "HTTPMethod.h"

HTTPRequestMessage(float version, HTTPMethod method, std::string path, headerMap headers, std::string data = NULL)
{
    this->version = version;
    this->method = method;
    this->path = path;
    HTTPMessage::HTTPMessage(headers, data);
}
HTTPMethod HTTPRequestMessage::getMethod()
{
    return this->method;
}
std::string HTTPRequestMessage::getPath()
{
    return this->path;
}
std::string HTTPRequestMessage::format()
{
    std::string output;
    output += this->method.value();
    output += " ";
    output += this->path;
    output += " HTTP/";
    output += this->version;
    output += "\r\n";
    for (auto &[key, value] : this->headers)
    {
        output += key;
        output += ": ";
        output += value;
        output += "\r\n"
    }
    ouput += "\r\n";
    ouput += data;
    output += "\n\0";
}
