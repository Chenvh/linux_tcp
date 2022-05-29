#include "t_net.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

//子进程终止时给父进程发送SIGCHLD信号
void handle(int n){
    //回收子进程的资源
    wait(NULL);
    return ;
}
extern int t_main(int cfd);
int main(void){
    //创建一个socket设备,返回该设备的文件描述符
    signal(SIGCHLD,handle);
    char buffer[128];
    SA4 cli;
    int s_fd = s_listen(AF_INET,SOCK_STREAM,8000,5);
    if(s_fd == -1){
        return -1;
    }
    while(1){
          int cfd = h_acpt(s_fd);
          if(cfd == -1) return -1;
          pid_t pid = fork();
          //父子进程是异步的
          if(pid == -1){
             printf("%s\n",strerror(errno));
             return -1;
          }
          
if(pid == 0){
            close(s_fd);
            t_main(cfd);
            close(cfd);
            exit(0);
          }
          else{
            close(cfd);
            //阻塞等待
            //waitpid(-1,NULL,WNOHANG);
          }
    }
    close(s_fd);
    return 0;
}

