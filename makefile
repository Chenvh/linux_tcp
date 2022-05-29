tcp: server_tcp.c client_tcp.c tcp.h
	gcc server_tcp.c -o server_tcp
	gcc client_tcp.c -o client_tcp

.PHONY: clean
clean:
	rm server_tcp client_tcp tcp_server.log