#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <netdb.h>
#define PORT (u_short)9000

int main(){
  int s_listen;
  char hostname[256];
  struct hostent *myhost;
  struct sockaddr_in me;
  /*�����åȤ����*/
  if ((s_listen = socket(AF_INET, SOCK_STREAM,0)) < 0 ) {
    fprintf(stderr,"Socket for server failed.\n");
    return -1;
  }
  /*���ۥ���̾�ȣɣХ��ɥ쥹�μ���*/
  gethostname(hostname,256);
  printf("%s\n",hostname);
  myhost = gethostbyname(hostname);
  if(myhost == NULL) {
    fprintf(stderr,"bad hostname!\n");
    return -1;
  } 
  /*���ۥ��Ⱦ����¤�Τ˥��å�*/
  bzero((char *)&me,sizeof(me));
  me.sin_family = AF_INET;
  me.sin_port = htons(PORT);
  bcopy(myhost->h_addr, (char *)&me.sin_addr, myhost->h_length);
  /*�����åȤ˥��ɥ쥹�ȥݡ����ֹ��Х���ɤ���*/
  if (bind(s_listen, &me, sizeof(me)) == -1) {
    fprintf(stderr, "Server could not bind.\n");
    return -1;
  }
  return 0;
}
