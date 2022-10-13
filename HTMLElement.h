#ifndef HTML_ELEMENT_H
#define HTML_ELEMENT_H

#include <string>
#include <list>
#include <map>
#include <functional>
class HTMLElement
{
private:
    std::string type;
    std::string content;
    std::map<std::string, std::string> attributes;
    std::list<HTMLElement> children;
    /**
     * Create element attributes from string
     */
    static std::map<std::string, std::string> parseAttributes(std::string doc);

public:
    /**
     * Create HTML Element. Creates children from content string
     */
    HTMLElement(std::string type, std::map<std::string, std::string> attributes, std::string content);
    /**
     * Get HTML type of element
     */
    std::string getType();
    /**
     * Create HTML Element list from HTML document
     */
    static std::list<HTMLElement> parseDocument(std::string doc);
    /**
     * Create HTML Element list from string
     */
    static std::list<HTMLElement> parseElements(std::string doc);
    /**
     * Search for elements and children of elements in list where function evaluates as true
     */
    static std::list<HTMLElement> search(std::list<HTMLElement> list, const std::function<bool(HTMLElement)> &f);
    /**
     * Get element attributes
     */
    std::map<std::string, std::string> getAttributes();
    /**
     * Get content inside element
     */
    std::string getContent();
};
#endif