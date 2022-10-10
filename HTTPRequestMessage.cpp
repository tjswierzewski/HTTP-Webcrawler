#include "HTTPRequestMessage.h"

HTTPRequestMessage::HTTPRequestMessage(float version, std::string method, std::string path, HTTPMessage::headerMap headers, std::string data) : HTTPMessage(headers, data)
{
    this->version = version;
    this->method = method;
    this->path = path;
}
std::string HTTPRequestMessage::getMethod()
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
    output += this->method;
    output += " ";
    output += this->path;
    output += " HTTP/";
    output += printVersion();
    output += "\r\n";
    for (auto &[key, value] : this->headers)
    {
        output += key;
        output += ": ";
        output += value;
        output += "\r\n";
    }
    output += "\r\n";
    output += data;
    output += "\n\0";

    return output;
}
