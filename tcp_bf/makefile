server: server.o t_net.o
	gcc -o server server.o t_net.o 

client: client.o t_net.o
	gcc -o client client.o t_net.o

t_net.o: t_net.c t_net.h
	gcc -c t_net.c

server.o: server.c 
	gcc -c server.c

client.o: client.o t_net.c t_net.h
	gcc -c client.c


.PHONY : clean
clean :
	rm server client t_net.o server.o client.o