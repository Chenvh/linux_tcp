#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/param.h> 
#include <sys/stat.h> 

void init_daemon(void) 
{ 
    int pid; 
    int i; 
    if(pid=fork()) 
    exit(0);//是父进程，结束父进程 
    else if(pid< 0) 
    exit(1);//fork失败，退出 
    //是第一子进程，后台继续执行 
    setsid();//第一子进程成为新的会话组长和进程组长 
    //并与控制终端分离 
    if(pid=fork()) 
    exit(0);//是第一子进程，结束第一子进程 
    else if(pid< 0) 
    exit(1);//fork失败，退出 
    //是第二子进程，继续 
    //第二子进程不再是会话组长 
    for(i=0;i< NOFILE;++i)//关闭打开的文件描述符 
    close(i); 
    //chdir("/tmp");//改变工作目录到/tmp 
    umask(0);//重设文件创建掩模 
    return; 
}
 
int  main()
{
    FILE *fp; 
    time_t t; 
     
    pid_t pid;
    int ser_socket;
    struct sockaddr_in se_addr,cl_addr;
    int addr_len = sizeof(cl_addr);
    int client;
    char buffer[4000],renew[4000];
    int datanum;
	int listenfd;
	int reuse = 0;
	struct sockaddr_in cliaddr, servaddr;    

    init_daemon();//初始化为Daemon

    if ((ser_socket = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("socket");
        return -1;
    }
    
    bzero(&se_addr, sizeof(se_addr));
    se_addr.sin_family = AF_INET;
    se_addr.sin_port = htons(5901);
    se_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	listenfd = socket(PF_INET, SOCK_STREAM,0);
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
	{
			perror("setsockopet error\n");
			return -1;
	}	

    if(bind(ser_socket,(struct sockaddr *)&se_addr,sizeof(se_addr))<0)
    {
        perror("bind");
        return -1;
    }
    
    if(listen(ser_socket, 10)<0)
    {
        perror("listen");
        return -1;
    }

    //等待请求
    while (1) {
        printf("Listening on port :%d\n",5901);
        client = accept(ser_socket, (struct sockaddr*)&cl_addr, (socklen_t *)&addr_len);
        if(client<0)
        {
            perror("accept");
            continue;
        }
        printf("\n recv client data:\n");
        printf("IP is %s\n",inet_ntoa(cl_addr.sin_addr));
        printf("port is %d\n",htons(cl_addr.sin_port));
        //进行对话,创建线程
        if((pid = fork())==0)
        {
         close(ser_socket);
        while(1)
        {           
            datanum = recv(client, buffer, 4000, 0);// 收数据
            if(datanum< 0)
            {
                perror("recv");
                continue;
            }
            buffer[datanum] = '\0';
            printf("%d:say %s\n", htons(cl_addr.sin_port), buffer);
            // printf("you want to say:");
            // scanf("%s",renew);
            if((fp=fopen("tcp_server.log","a")) >=0) 
            { 
                fprintf(fp, "%d:say %s\n", htons(cl_addr.sin_port), buffer);
                fclose(fp); 
            }    
            send(client, "服务端受到消息", strlen("服务端受到消息"), 0);          
            send(client, buffer, strlen(renew), 0);
            if(strcmp(renew, "quit") == 0)
            {
                exit(0);//销毁此线程
                break;
            }
        }
        }
    }
    
    return 0;
}