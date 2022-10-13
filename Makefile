CC = g++
DFLAGS = -gdwarf-2 -g3 -O0 -D_GLIBCXX_DEBUG
CFLAGS = -std=c++17
LIBS = -L/usr/lib/ssl/lib -lssl -lcrypto


webcrawler: webcrawler.o http.a HTMLElement.o
	${CC} $^ ${CFLAGS} -o $@ ${LIBS}

webcrawler.o: webcrawler.cpp
	${CC} -c $< ${CFLAGS} -o $@

http.a: HTTPSSession.o HTTPMessage.o HTTPRequestMessage.o HTTPResponseMessage.o HTTPMethod.o
	ar cr $@ $^

HTTPSSession.o: HTTPSSession.cpp
	${CC} -c $< ${CFLAGS} -o $@

HTTPMessage.o: HTTPMessage.cpp
	${CC} -c $< ${CFLAGS} -o $@

HTTPResponseMessage.o: HTTPResponseMessage.cpp
	${CC} -c $< ${CFLAGS} -o $@

HTTPRequestMessage.o: HTTPRequestMessage.cpp
	${CC} -c $< ${CFLAGS} -o $@

HTTPMethod.o: HTTPMethod.cpp
	${CC} -c $< ${CFLAGS} -o $@

HTMLElement.o: HTMLElement.cpp
	${CC} -c $< ${CFLAGS} -o $@

HTMLTest: HTMLElement.cpp HTMLTest.cpp
	${CC} $^ ${CFLAGS} -o $@ -L/usr/lib/aarch64-linux-gnu/debug/libstdc++.so.6

clean:
	rm -f webcrawler webcrawler.o HTTPSSession.o HTTPMessage.o HTTPRequestMessage.o HTTPResponseMessage.o http.a
	rm -f HTMLTest HTMLElement.o HTTPMethod.o log.key html