#include <iostream>
#include <string.h>
#include <string>
#include "HTTPSession.h"

#define HOST "project2.5700.network"
#define PORT "443"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./webcrawler [username] [password]" << std::endl;
    }
    char buffer[MAX_LENGTH];
    HTTPSSession session(HOST, PORT);

    HTTPResponseMessage res = session.get("/", buffer, MAX_LENGTH);

    std::cout << res.getData() << std::endl;

    return 0;
}
