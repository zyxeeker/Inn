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
struct s_info{
    struct  sockaddr_in cliaddr;
};

void  *do_work(void *arg){

}


int main(int argc,char *argv[]){
    struct sockaddr_in servaddr,cliaddr;
    socklen_t  cliaddr_len;
    int listenfd ,connfd;
    pthread_t  tid;

    struct  s_info ts[256];
    int i=0;

    listenfd =socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr,sizeof(servaddr));
    serv_addr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);  //指定本地任意IP
    serv_addr.sin_port = htons(9006);  //指定服务器端口号

    bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(listenfd,128);

    std::cout<<"accepting client connect ..."<<std::endl;

    //serv_addr->sin_addr.s_addr=htonl(INADDR_ANY);  //INADDR_ANY为任意有效ip地址
    while(1){
            cliaddr_len =sizeof(cliaddr);
            connfd=accept(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr));  //阻塞监听客户端链接请求
            ts[i],cliaddr =cliaddr;
            ts.[i]connfd = connfd;

            pthread_create(&tid,NULL,do_work,(void *)&ts[i]);
            pthread_detach(tid);
            i++;



    }
    return 0;
}