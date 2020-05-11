#pragma once

#include <stdio.h>
#include <errno.h>
void checkerror(int ret, char* msg) {
  if (ret < 0) {
    perror(msg);
    exit(EXIT_FAILURE);
  }
}
