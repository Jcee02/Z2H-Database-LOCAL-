#include <unistd.h>
#include <stdio.h>
#include "parse.h"


int parse_database_header(int fd, int *numItemsInDatabase) {
  if (fd == -1) {
    printf("Bad file descriptor provided\n");
    return fd;
  }

  struct db_header_t header = {0};
  if (read(fd, &header, sizeof(header)) != sizeof(header)) {
    printf("Failed to read header file\n.");
    return fd;
  }
  
  *numItemsInDatabase = header.count;
  return 0;

}



