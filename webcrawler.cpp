#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <set>
#include "HTTPSSession.h"
#include "HTMLElement.h"

#define HOST "project2.5700.network"
#define PORT "443"

/**
 * Function for determining if HTML element is a link element
 */
bool isLink(HTMLElement element)
{
    return element.getType() == "a";
}

/**
 * Function for determining if HTML element is a csrf element
 */
bool isCSRF(HTMLElement element)
{
    return element.getType() == "input" && element.getAttributes()["name"] == "csrfmiddlewaretoken";
}

/**
 * Function for determining if HTML element is a secret flag element
 */
bool isSecret(HTMLElement element)
{
    return element.getContent().find("FLAG: ") != std::string::npos;
}

/**
 * Main script for web crawler
 */
int main(int argc, char const *argv[])
{
    // Check args
    if (argc != 3)
    {
        std::cout << "Usage: ./webcrawler [username] [password]" << std::endl;
        exit(1);
    }
    // Create and connect HTTPS session
    HTTPSSession session(HOST, PORT);

    // Login to Fakebook
    std::ostringstream loginPost;
    HTTPResponseMessage res = session.get("/fakebook/");
    std::list<HTMLElement> html = HTMLElement::parseDocument(res.getData());
    std::list<HTMLElement> out = HTMLElement::search(html, isCSRF);
    std::string csrf = (*(out.begin())).getAttributes()["value"];
    loginPost << "username=" << argv[1] << "&password=" << argv[2] << "&csrfmiddlewaretoken=" << csrf << "&next=%2Ffakebook%2F";
    res = session.post("/accounts/login/?next=/fakebook/", loginPost.str(), "application/x-www-form-urlencoded");

    // Crawl Fakebook for secret tags
    int count = 0;
    std::deque<std::string> toCheck;
    std::set<std::string> checked, found;
    toCheck.push_back("/fakebook/");
    checked.insert("/");
    found.insert("/");
    checked.insert("/accounts/logout/");
    found.insert("/accounts/logout/");
    while (count < 5 && !toCheck.empty())
    {
        // Get first path in queue
        std::string path = toCheck.front();
        toCheck.pop_front();

        // Make GET request
        res = session.get(path);

        // Skip if 400
        if (res.getStatus() == 403 || res.getStatus() == 404)
        {
            continue;
        }
        // Try path again if 500
        if (res.getStatus() == 500)
        {
            toCheck.push_front(path);
            continue;
        }
        // Path checked
        checked.insert(path);

        // Parse HTML Document
        html = HTMLElement::parseDocument(res.getData());

        // Check for links in HTML
        std::list<HTMLElement> links = HTMLElement::search(html, isLink);
        for (auto &&element : links)
        {
            std::string newPath = element.getAttributes()["href"];
            if (newPath[0] == '/' && checked.count(newPath) == 0 && found.count(newPath) == 0)
            {
                toCheck.push_back(newPath);
                found.insert(newPath);
            }
        }

        // Check for secret flags in HTML
        std::list<HTMLElement> secrets = HTMLElement::search(html, isSecret);
        for (auto &&element : secrets)
        {
            std::cout << element.getContent().substr(6) << std::endl;
            count++;
        }
    };

    return 0;
}
