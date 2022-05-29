target:
	gcc server_tcp.c -o server_tcp
	gcc client_tcp.c -o client_tcp

clean:
	rm server_tcp client_tcp