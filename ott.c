#include "CmBurnServer.h"
 
int main(int argc, char *argv[])
{
    int fd = -1, ret = -1;

    /*1.�����׽��� */
    if( (fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    { //����һ��TCP��Internetͨ��
        perror("==========socket");
        exit(1);
    }
 
    /*2.���ӷ�����*/
    /* 2.1 ��д��������IP��ַ�Ͷ˿ں� */
     struct sockaddr_in sin;
      bzero(&sin, sizeof(sin));
      sin.sin_family =AF_INET;
      sin.sin_port = htons(SERV_PORT);//�ѱ����ֽ���ת��Ϊ�����ֽ���
      sin.sin_addr.s_addr = inet_addr(SERV_IP);//�� x.x.x.x �����ַת��Ϊ�ַ���
 
    /*2.2 ���� */
      if(connect(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
            perror("==========connect");
            exit(1);
      }
      printf("==========Client starting....ok!\n");       
      /*3. �ӱ�׼�ն��ϻ�ȡ�û�����,���͵�������*/
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
 
        if( !ret || !strncasecmp(buf, QUIT_STR, strlen(QUIT_STR)) ) { //�Է��Ѿ��رջ�ͻ���������quit
            break;
        }
 
      }
    close(fd);
 
    return 0;
}