#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
using namespace std;

int main() {
    struct sockaddr_in server;
    int sock;

    // create and connect socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_family = AF_INET;
    server.sin_port = htons(12345);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sock, (struct sockaddr *)&server, sizeof(server));

    // send and receive message
    string message;
    char buf[1024];

    while (cin >> message) {
        send(sock, message.c_str(), (int)(message.length()+1), 0);

        memset(buf, 0, sizeof(buf));
        int n = read(sock, buf, sizeof(buf));

        cout << n << buf << endl;
    }
    close(sock);
    return 0;
}

