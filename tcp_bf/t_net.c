#include "t_net.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
int bind_sock(int domain,int type,u_int16_t port){
    //创建一个socket设备,返回该设备的文件描述符
    SA4 serv;
    int sfd = socket(domain,type,0);
    if(sfd == -1){
        printf("%s\n",strerror(errno));
        return -1; 
    }   
    //将sfd绑定绑定本地地址
    serv.sin_family = AF_INET;
    //主机字节序到网络字节序
    serv.sin_port = htons(port);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
    int b = bind(sfd,(SA*)&serv,sizeof(serv));
    if(b == -1){
        printf("%s\n",strerror(errno));
        return -1;
    }
    return sfd;
}

//不显示显示客户端的IP
int n_acpt(int fd){
    int cfd = accept(fd,NULL,NULL);
    if(cfd == -1){
        printf("%s\n",strerror(errno));
    }
    return cfd;
}

//显示客户端的IP地址
int h_acpt(int fd){
    SA4 cli;
    char ip[32];
    socklen_t len = sizeof(cli);
    int cfd = accept(fd,(SA*)&cli,&len);
    if(cfd == -1){
        printf("%s\n",strerror(errno));
        return -1;
    }
    printf("%s\n",inet_ntop(AF_INET,&cli.sin_addr,ip,32));
    return cfd;
}

int t_main(int cfd){
    //读取客户端的请求消息,read阻塞
    char buf[128];
    while(1){
        int r = read(cfd,buf,128);
        for(int i = 0;i < r ;i++)
            buf[i] = toupper(buf[i]);
        write(cfd,buf,r);
        if(strcmp(buf,"BYEBYE") == 0) break;
    }   
    return 0;
}