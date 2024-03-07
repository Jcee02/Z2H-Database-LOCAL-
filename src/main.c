#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "parse.h"


int main(int argc, char *argv[1]){
  int fd, numItems = 0;

  if (argc != 2) {
    printf("Usage: %s <filename>", argv[0]);
    return EXIT_SUCCESS;
  }
  
  fd = open_file_rw(argv[1]);
   if (fd == -1) 
    return -1;

  if (parse_database_header(fd, &numItems))
    return -1;

  printf("Number of items stored: %u\n", numItems);

  return EXIT_SUCCESS;
}
