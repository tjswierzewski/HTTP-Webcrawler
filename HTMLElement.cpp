#include "HTMLElement.h"

HTMLElement(std::string type, std::string content)
{
    this->type = type;
    this->content = content;
}
static std::list<HTMLElement> parseDocument(std::string doc)
{
    // Read tag of element if opening make new element. Keep elements in a stack.
    // Before removing the last element from the stack put element in document.

    // Make list thats when searched also searches list in elements
}