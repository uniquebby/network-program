#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string.h>
#include <stdlib.h>

#include "checkerror.h"
int main(int argc, char *argv[]) {
  int connectfd;
  int ret;

  connectfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  checkerror(connectfd, "socket");

  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port= htons(8888);
  //servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

  ret = connect(connectfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
  checkerror(ret, "connect");

  char wbuf[1024] = {0};
  char rbuf[1024] = {0};
  while (fgets(wbuf, sizeof(wbuf), stdin) != NULL) {
    write(connectfd, wbuf, sizeof(wbuf));
    memset(rbuf, 0, sizeof(rbuf));
    read(connectfd, rbuf, sizeof(rbuf));
    fputs(rbuf, stdout);
  }
  close(connectfd);
}
