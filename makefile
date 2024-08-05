BINARIES = tcp_server tcp_client

all : $(BINARIES)

tcp_server : tcp_server.c
	gcc -ggdb -Wall -Wextra tcp_server.c -o tcp_server

tcp_client : tcp_client.c
	gcc -ggdb -Wall -Wextra tcp_client.c -o tcp_client

clean :
	rm $(BINARIES)

