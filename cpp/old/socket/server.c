#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define BUFFER_SIZE 256

int
main() {
  /* �ݡ����ֹ桢�����å� */
  unsigned short port = 9876;
  int srcSocket;  // ��ʬ
  int dstSocket;  // ���

  /* sockaddr_in ��¤�� */
  struct sockaddr_in srcAddr;
  struct sockaddr_in dstAddr;
  int dstAddrSize = sizeof(dstAddr);

  /* �Ƽ�ѥ�᡼�� */
  int numrcv;
  char buffer[BUFFER_SIZE];

  /************************************************************/
  /* sockaddr_in ��¤�ΤΥ��å� */
  memset(&srcAddr, 0, sizeof(srcAddr));
  srcAddr.sin_port = htons(port);
  srcAddr.sin_family = AF_INET;
  srcAddr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* �����åȤ����� */
  srcSocket = socket(AF_INET, SOCK_STREAM, 0);

  /* �����åȤΥХ���� */
  bind(srcSocket, (struct sockaddr *) &srcAddr, sizeof(srcAddr));

  /* ��³�ε��� */
  listen(srcSocket, 5);

  /* ��³�μ��դ� */
  printf("Waiting for connection ...\n");
  dstSocket = accept(srcSocket, (struct sockaddr *) &dstAddr, &dstAddrSize);
  printf("Connected from %s\n", inet_ntoa(dstAddr.sin_addr));

  /* �ѥ��åȼ��� */
  while(1) {
    numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0); 
    if(numrcv == 0 || numrcv == -1) {
      close(dstSocket); break;
    }
    printf("received: %s\n", buffer);

    char toSendText[] = "�錄����̾���ϱ���Ǥ���";
    send(dstSocket, toSendText, strlen(toSendText)+1, 0);
  }
}
