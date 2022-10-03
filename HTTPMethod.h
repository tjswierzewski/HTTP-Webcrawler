#ifndef HTTP_METHOD_H
#define HTTP_METHOD_H

#include <string>

class HTTPMethod
{
public:
    static std::string Get;
    static std::string Post;
    static std::string Patch;
    static std::string Delete;
    static std::string Put;
    static std::string Head;
    static std::string Options;
    static std::string Connect;
    static std::string Trace;
};
std::string HTTPMethod::Get = "GET";
std::string HTTPMethod::Post = "POST";
std::string HTTPMethod::Patch = "PATCH";
std::string HTTPMethod::Delete = "DELETE";
std::string HTTPMethod::Put = "PUT";
std::string HTTPMethod::Head = "HEAD";
std::string HTTPMethod::Options = "OPTIONS";
std::string HTTPMethod::Connect = "CONNECT";
std::string HTTPMethod::Trace = "TRACE";
#endif