#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

#define MAX_LENGTH 10000

#include <string>
#include <map>

class HTTPMessage
{
public:
    typedef std::multimap<std::string, std::string> headerMap;

protected:
    float version;
    headerMap headers;
    std::string data;
    void parseHeaders(std::string *buffer);

public:
    HTTPMessage(std::string buffer);
    HTTPMessage(headerMap headers, std::string data = "");
    float getVersion();
    headerMap getHeaders();
    std::string getData();
    std::string printVersion();
    void setHeader(std::string key, std::string value);
    void setData(std::string data);
};
#endif