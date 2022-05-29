#ifndef __T_NET_H__
#define __T_NET_H__
#include <sys/socket.h>
#include <sys/types.h>
typedef struct sockaddr SA; 
typedef struct sockaddr_in SA4;
//socket bind
//这里将套接字的创建过程和绑定过程封装为一个函数
int bind_sock(int domain,int type,u_int16_t port);
//调用这个函数可以从未连接队列中取出一个进行处理.不会显示
//客户端的ip地址
int n_acpt(int fd);
//对比上一个函数,可以显示客户端的ip地址
int h_acpt(int fd);
//将套接字的创建 绑定 监听封装到一个函数中
int s_listen(int domain,int type,u_int16_t port,int b); 

int t_main(int cfd);
#endif //__T_NET_H__

