#include "t_net.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc,char* argv[]){
    //创建套接字
    char msg[128];
    if(argc < 2){
        printf("参数过少\n");
        return 0;
    }
    int cfd = socket(AF_INET,SOCK_STREAM,0);
    if(cfd == -1){
        printf("%s\n",strerror(errno));
        return 0;
    }
	 //向服务器发起请求
    SA4 addr;
    memset(&addr,0,sizeof(addr));
    addr.sin_family = AF_INET;
    //端口号
    addr.sin_port = htons(8000);
    char *ipaddress = argv[1];
    struct in_addr ip;
    inet_pton(AF_INET,ipaddress,&ip);
    addr.sin_addr = ip;
    int ret = connect(cfd,(SA*)&addr,sizeof(SA));
    if(ret == 0){
        printf("连接成功...\n");
    }
    else{
        printf("连接失败...\n");
        return 0;
    }
    while(1){
     gets(msg);
        write(cfd,msg,sizeof(msg));
        char rbuf[128];
        int r = read(cfd,rbuf,sizeof(rbuf));
        printf("message from server:\n");
        printf("%s\n",rbuf);
        if(strcmp(rbuf,"BYEBYE") == 0) break;
    }
    close(cfd);
    return 0;
}

