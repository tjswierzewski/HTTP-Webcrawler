#include <iostream>
#include <string.h>
#include <string>
#include "HTTPSSession.h"
#include <fstream>

#define HOST "project2.5700.network"
#define PORT "443"

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./webcrawler [username] [password]" << std::endl;
    }
    HTTPSSession session(HOST, PORT);

    HTTPResponseMessage res = session.get("/");

    std::ofstream myFile;
    myFile.open("html");
    myFile << res.getData();
    myFile.close();

    // Keep track of searched pages in set

    return 0;
}
