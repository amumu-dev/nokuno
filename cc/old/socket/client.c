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

  /* IP アドレス、ポート番号、ソケット */
  char destination[] = "127.0.0.1";
  unsigned short port = 9876;
  int dstSocket;

  /* sockaddr_in 構造体 */
  struct sockaddr_in dstAddr;

  /* 各種パラメータ */
  int numsnt;
  char *toSendText = "わたしのなまえはおくのです。";

  int numrcv;
  char buffer[BUFFER_SIZE];

  /************************************************************/
  /* 相手先アドレスの入力 */
  //printf("Connect to ? : (name or IP address) ");
  //scanf("%s", destination);

  /* sockaddr_in 構造体のセット */
  memset(&dstAddr, 0, sizeof(dstAddr));
  dstAddr.sin_port = htons(port);
  dstAddr.sin_family = AF_INET;
  dstAddr.sin_addr.s_addr = inet_addr(destination);
 
  /* ソケット生成 */
  dstSocket = socket(AF_INET, SOCK_STREAM, 0);

  /* 接続 */
  printf("Trying to connect to %s: \n", destination);
  connect(dstSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr));

  /* パケット送出 */
  printf("sending...\n");
  send(dstSocket, toSendText, strlen(toSendText)+1, 0);
  
  numrcv = recv(dstSocket, buffer, BUFFER_SIZE, 0); 
  if(numrcv == 0 || numrcv == -1) {
    close(dstSocket);
    return;
  }
  printf("client received: %s\n", buffer);

  /* ソケット終了 */
  close(dstSocket);
}
