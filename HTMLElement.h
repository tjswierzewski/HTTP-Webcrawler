#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H

#include <string>
#include <list>

class HTMLElement
{
private:
    std::string type;
    std::string content;
    std::string attributes;
    std::list<HTMLElement> children;

public:
    HTMLElement(std::string type, std::string attributes, std::string content);
    // Make list of HTML Elements that is search able to children level
    static std::list<HTMLElement> parseDocument(std::string doc);
    static std::list<HTMLElement> parseElements(std::string doc);
};
#endif