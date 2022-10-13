# C++ Webcrawler


My approach for this project was to make a library that would be responsible for the HTTP session with the server.
Once I could send messages back and forth with the server I made a library to parse the HTML into element classes.
Using these two libraries I made a web crawler that makes a request to a website and follows any links that are on the response page.

I used wireshark to view TLS errors I was getting due to the formatting of my HTTP requests. I also made a test program so
that I could debug the HTML library without pinging the server repeatedly.

The main issue I ran into while implementing the HTTP library was correctly formatting the end of the message correctly.
I also struggled with reading the correct size from the socket. I fixed this by reading the HTTP header one byte at a time until
the double return. After that I check if there is a content length field and read that amount from the socket.