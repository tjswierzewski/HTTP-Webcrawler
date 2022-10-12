#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include "HTTPSSession.h"
#include "HTMLElement.h"

#define HOST "project2.5700.network"
#define PORT "443"

bool isLink(HTMLElement element)
{
    return element.getType() == "a";
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./webcrawler [username] [password]" << std::endl;
    }
    HTTPSSession session(HOST, PORT);

    HTTPResponseMessage res = session.get("/");

    std::list<HTMLElement> html = HTMLElement::parseDocument(res.getData());

    std::list<HTMLElement> out = HTMLElement::search(html, isLink);

    return 0;
}
