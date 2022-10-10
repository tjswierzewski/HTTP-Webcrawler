CC = g++
DFLAGS = -gdwarf-2 -g3 -O0 -D_GLIBCXX_DEBUG
CFLAGS = -std=c++17
LIBS = -L/usr/lib/ssl/lib -lssl -lcrypto


webcrawler: webcrawler.o http.a
	${CC} $^ ${DFLAGS} ${CFLAGS} -o $@ ${LIBS}

webcrawler.o: webcrawler.cpp
	${CC} -c $< ${DFLAGS} ${CFLAGS} -o $@

http.a: HTTPSSession.o HTTPMessage.o HTTPRequestMessage.o HTTPResponseMessage.o HTTPMethod.o
	ar cr $@ $^

HTTPSSession.o: HTTPSSession.cpp
	${CC} -c $< ${DFLAGS} ${CFLAGS} -o $@

HTTPMessage.o: HTTPMessage.cpp
	${CC} -c $< ${DFLAGS} ${CFLAGS} -o $@

HTTPResponseMessage.o: HTTPResponseMessage.cpp
	${CC} -c $< ${DFLAGS} ${CFLAGS} -o $@

HTTPRequestMessage.o: HTTPRequestMessage.cpp
	${CC} -c $< ${DFLAGS} ${CFLAGS} -o $@

HTTPMethod.o: HTTPMethod.cpp
	${CC} -c $< ${DFLAGS} ${CFLAGS} -o $@

HTMLElement.o: HTMLElement.o
	${CC} -c $< ${DFLAGS} ${CFLAGS} -o $@
clean:
	rm -f webcrawler webcrawler.o HTTPSSession.o HTTPMessage.o HTTPRequestMessage.o HTTPResponseMessage.o http.a