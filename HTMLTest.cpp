#include "HTMLElement.h"
#include <fstream>
#include <sstream>
#include <list>

/**
 * Test for HTML Element
 */
int main(int argc, char const *argv[])
{
    std::ifstream doc;
    doc.open("html");
    std::stringstream buffer;
    buffer << doc.rdbuf();

    std::list<HTMLElement> out = HTMLElement::parseDocument(buffer.str());
    return 0;
}
