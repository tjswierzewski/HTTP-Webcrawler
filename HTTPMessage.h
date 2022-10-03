#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H
#define MAX_LENGTH 10000

#include <string>
#include <map>

class HTTPMessage
{
protected:
    float version;
    typedef std::map<std::string, std::string> headerMap;
    headerMap headers;
    std::string data;
    void parseHeaders(std::string *buffer);

public:
    HTTPMessage(std::string buffer);
    HTTPMessage(headerMap headers, std::string data /*""*/);
    float getVersion();
    headerMap getHeaders();
    std::string getData();
};
#endif