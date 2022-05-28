#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
 
 
int main(int argc, const char * argv[]) {
    int client_socket;
    struct sockaddr_in ser_addr;
    char sendbuf[400];
    char recbuf[400];
    int sennum,recnum;
	int listenfd;
	int reuse = 0;
	struct sockaddr_in cliaddr, servaddr;  

    if((client_socket= socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        perror("socket");
        return -1;
    }
    
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(5901);
    ser_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

 	listenfd = socket(PF_INET, SOCK_STREAM,0);
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
	{
			perror("setsockopet error\n");
			return -1;
	}	

    if(connect(client_socket, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
    {
        perror("connect");
        return 1;
    }
    
    printf("connect with destination host...\n");
    
    while(1)
    {
        printf("Input your world:>");
        scanf("%s", sendbuf);
        printf("\n");
        
        send(client_socket, sendbuf, strlen(sendbuf), 0);
        
        recnum = recv(client_socket, recbuf, 4000, 0);
        recbuf[recnum] = '\0';
        printf("recv is: %s\n", recbuf);
        if(strcmp(recbuf, "quit") == 0)
            break;
    }
    close(client_socket);
    
    return 0;
}