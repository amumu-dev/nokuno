#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 256

int
main() {
  int i;

  /* IP ���ɥ쥹���ݡ����ֹ桢�����å� */
  char destination[] = "127.0.0.1";
  unsigned short port = 9876;
  int dstSocket;

  /* sockaddr_in ��¤�� */
  struct sockaddr_in dstAddr;

  /* �Ƽ�ѥ�᡼�� */
  int numsnt;
  char *toSendText = "�錄���Τʤޤ��Ϥ����ΤǤ���";

  int numrcv;
  char buffer[BUFFER_SIZE];

  /************************************************************/
  /* ����襢�ɥ쥹������ */
  //printf("Connect to ? : (name or IP address) ");
  //scanf("%s", destination);

  /* sockaddr_in ��¤�ΤΥ��å� */
  memset(&dstAddr, 0, sizeof(dstAddr));
  dstAddr.sin_port = htons(port);
  dstAddr.sin_family = AF_INET;
  dstAddr.sin_addr.s_addr = inet_addr(destination);
 
  /* �����å����� */
  dstSocket = socket(AF_INET, SOCK_STREAM, 0);

  /* ��³ */
  printf("Trying to connect to %s: \n", destination);
  connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr));

  /* �ѥ��å����� */
  printf("sending...\n");
  send(dstSocket, toSendText, strlen(toSendText)+1, 0);
  
  numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0); 
  if(numrcv == 0 || numrcv == -1) {
    close(dstSocket);
    return;
  }
  printf("client received: %s\n", buffer);

  /* �����åȽ�λ */
  close(dstSocket);
}
