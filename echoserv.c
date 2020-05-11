#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdlib.h>

#include "checkerror.h"
#include "printaddr.h"
int main(int argc, char *argv[]) {
  int listenfd;
  int ret;

  listenfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  checkerror(listenfd, "socket");

  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port= htons(8888);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  ret = bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
  checkerror(ret, "bind");

  ret = listen(listenfd, SOMAXCONN);
  checkerror(ret, "listen");

  struct sockaddr_in peeraddr;
  socklen_t peerlen = sizeof(peeraddr);
  
  int conn = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen);
  checkerror(conn, "accept");
  //printaddr(&peeraddr);

  char rbuf[1024];
  for (;;) {
    memset(rbuf, 0, sizeof(rbuf));
    read(conn, rbuf, sizeof(rbuf));
    fputs(rbuf, stdout);
    write(conn, rbuf, sizeof(rbuf));
  }
  close(conn);
  close(listenfd);
}
