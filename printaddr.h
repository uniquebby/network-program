#pragma once

#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

void printaddr(struct sockaddr_in *addr) {
  printf("ip = %s port = %d", inet_ntoa(addr->sin_addr), ntohs(addr->sin_port));
}
