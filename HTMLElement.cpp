#include "HTMLElement.h"
#include <string>
#include <list>
#include <sstream>

HTMLElement::HTMLElement(std::string type, std::string attributes, std::string content)
{
    this->type = type;
    this->attributes = attributes;
    if (content.find_first_of("<") == std::string::npos)
    {
        this->content = content;
    }
    else
    {
        this->content = "";
        this->children = HTMLElement::parseElements(content);
    }
}
std::list<HTMLElement> HTMLElement::parseDocument(std::string doc)
{
    int HTMLOpen = doc.find_first_of("<!");
    int HTMLClose = doc.find_first_of(">", HTMLOpen);
    doc.erase(0, HTMLClose + 1);
    return HTMLElement::parseElements(doc);
}

std::list<HTMLElement> HTMLElement::parseElements(std::string doc)
{
    std::string attributes = "";
    std::string type = "";
    std::string content = "";
    std::list<HTMLElement> elements;
    int HTMLOpen, HTMLClose = 0;
    while ((HTMLOpen = doc.find("<", HTMLClose)) != std::string::npos)
    {
        HTMLClose = doc.find(">", HTMLOpen);
        if (doc[HTMLOpen + 1] == '!')
        {
            continue;
        }

        int typeSpace = doc.find(" ", HTMLOpen);
        if (typeSpace == std::string::npos || typeSpace > HTMLClose)
        {
            typeSpace = HTMLClose;
        }
        else
        {
            attributes = doc.substr(typeSpace + 1, HTMLClose - (typeSpace + 1));
        }
        type = doc.substr(HTMLOpen + 1, typeSpace - (HTMLOpen + 1));
        if (type != "meta" && type != "link" && type != "hr")
        {
            // figure out how to parse correct open and closing tags
            std::ostringstream startBuffer;
            std::ostringstream endBuffer;
            endBuffer << "</" << type << ">";
            startBuffer << "<" << type;
            int childStart = doc.find(startBuffer.str(), HTMLOpen + 1);
            HTMLOpen = doc.find(endBuffer.str(), HTMLClose);
            int childEnd = HTMLClose;
            while (childStart != std::string::npos && childStart < HTMLOpen)
            {
                childStart = doc.find(startBuffer.str(), childStart + 1);
                HTMLOpen = doc.find(endBuffer.str(), HTMLOpen + 1);
            }

            content = doc.substr(HTMLClose + 1, HTMLOpen - (HTMLClose + 1));
            HTMLClose = doc.find(">", HTMLOpen);
        }

        HTMLElement element(type, attributes, content);
        elements.push_back(element);
    }
    return elements;
}