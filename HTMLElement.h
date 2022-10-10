#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H

#include <string>

class HTMLElement
{
private:
    std::string type;
    std::string content;
    std::list<HTMLElement>;

public:
    HTMLElement(std::string type, std::string content);
    // Make list of HTML Elements that is search able to children level
    static std::list<HTMLElement> parseDocument(std::string doc);
};