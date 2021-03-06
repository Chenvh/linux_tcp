#include "tcp.h"
 
 
int main(int argc, const char * argv[]) {
    int client_socket;
    struct sockaddr_in ser_addr;
    char sendbuf[400];
    char recbuf[400];
    char ipv4_ddr[20];
    int sennum,recnum;
    int listenfd;
	int reuse = 0;
	struct sockaddr_in cliaddr, servaddr;  
    
    if((client_socket= socket(AF_INET, SOCK_STREAM, 0))<0)
    {
        perror("socket");
        return -1;
    }
    printf("input server ipv4_ddr: (enter d to set defualt host address)\n");
    scanf("%s",ipv4_ddr);
    if(ipv4_ddr[0] == 'd')
    {
        strcpy(ipv4_ddr,"127.0.0.1");
    }
    printf("ipv4_ddr is %s\n", ipv4_ddr);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(5901);
    ser_addr.sin_addr.s_addr = inet_addr(ipv4_ddr);
 	
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
        {
            close(client_socket);
            exit(0);
        }
    }

    
    return 0;
}
