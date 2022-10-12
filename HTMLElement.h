#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H

#include <string>
#include <list>
#include <map>

class HTMLElement
{
private:
    std::string type;
    std::string content;
    std::map<std::string, std::string> attributes;
    std::list<HTMLElement> children;
    static std::map<std::string, std::string> parseAttributes(std::string doc);

public:
    HTMLElement(std::string type, std::map<std::string, std::string> attributes, std::string content);
    static std::list<HTMLElement> parseDocument(std::string doc);
    static std::list<HTMLElement> parseElements(std::string doc);
};
#endif