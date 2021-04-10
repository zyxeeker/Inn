//
// Created by lz on 2021/4/10.
//
//
// Created by lz on 2021/4/10.
//
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>

void sys_err(const char *str){
    perror(str);
    exit(1);
}

int main(int argc,char *argv[]){

    char buf[9999];
    int cfd;
    //int conter =10;

    //std::cout<<"it  safe 1";
    struct sockaddr_in serv_addr; //服务器地址结构
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port = htons(9006); //服务器端口号
    //此处IP未填

    inet_pton(AF_INET,"192.168.3.27",&serv_addr.sin_addr);  //ip 暂时未填
    //serv_addr->sin_addr.s_addr=htonl(INADDR_ANY);  //INADDR_ANY为任意有效ip地址
    //std::cout<<"it  safe 3";
    cfd= socket(AF_INET,SOCK_STREAM,0);
    if(cfd == -1){
        sys_err("socket error");
    }
    //std::cout<<"it  safe 4";
    int ret =connect(cfd,(struct sockaddr * )&serv_addr,sizeof(serv_addr));//建立连接
    if(ret!=0){
        sys_err("connect error!");
    }
//以下为锁相关
//    int flag = fcntl(STDIN_FILENO,F_GETFL); //F_GETFL获取文件状态标志
//    flag |= O_NONBLOCK;
//    fcntl(STDIN_FILENO, F_SETFL, flag);
//
//    flag = fcntl(cfd, F_GETFL);
//    flag |= O_NONBLOCK;
//    fcntl(cfd, F_SETFL, flag);
//以上为锁相关，尚有疑问
    //std::cout<<"it  safe 5";
    while(1){


        std::cin>>buf;
        //write(cfd,"hello",6);  //向服务器写入hello
        send(cfd,buf,strlen(buf),0);

        /*ret =read(STDIN_FILENO,buf,strlen(buf));
        if(ret>0) write(cfd,buf,ret);

        if(!strncmp(buf,"exit",4)) break; //输入exit 结束连接

        ret = read(cfd,buf,strlen(buf));

        if(ret>0)  write(STDOUT_FILENO,buf,ret);
        //sleep(1); //每次操作休息一秒
        */

    }
    return 0;
}
