#include "CmBurnServer.h"
 
int main(int argc, char *argv[])
{
    int fd = -1, ret = -1;

    /*1.创建套接字 */
    if( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { //建立一个TCP的Internet通信
        perror("==========socket");
        exit(1);
    }
 
    /*2.连接服务器*/
    /* 2.1 填写服务器的IP地址和端口号 */
     struct sockaddr_in sin;
      bzero(&sin, sizeof(sin));
      sin.sin_family =AF_INET;
      sin.sin_port = htons(SERV_PORT);//把本地字节序转换为网络字节序
      sin.sin_addr.s_addr = inet_addr(SERV_IP);//把 x.x.x.x 网络地址转换为字符串
 
    /*2.2 连接 */
      if(connect(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
            perror("==========connect");
            exit(1);
      }
      printf("==========Client starting....ok!\n");       
      /*3. 从标准终端上获取用户输入,发送到服务器*/
      char buf[BUFSIZ];
      while(1) {
    fprintf(stderr, "==========pls input string:");
    bzero(buf, BUFSIZ);
    if( fgets(buf, BUFSIZ-1, stdin) == NULL) {
        continue;
    }
 
    do {
        ret = write(fd, buf, strlen(buf));
    }while(ret < 0 && EINTR == errno);
 
        if( !ret || !strncasecmp(buf, QUIT_STR, strlen(QUIT_STR)) ) { //对方已经关闭或客户端输入了quit
            break;
        }
 
      }
    close(fd);
 
    return 0;
}