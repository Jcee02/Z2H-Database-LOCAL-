#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "../include/parse.h"
#include "../include/status.h"

int add_employee(struct db_header_t *dbhdr, struct employee_t *employees, char *addstring) {
    char* name = strtok(addstring, ",");
    char* addr = strtok(NULL, ",");
    char* hours = strtok(NULL, ",");
    

    strncpy(employees[dbhdr->count-1].name, name, sizeof(employees[dbhdr->count-1].name));
    strncpy(employees[dbhdr->count-1].addr, addr, sizeof(employees[dbhdr->count-1].addr));
    employees[dbhdr->count-1].hours = atoi(hours);
  
}
int rd_employees(int fd, struct db_header_t *dbhdr, struct employee_t **employeeOut) {
  if (fd < 0) {
    printf("Invalid file descriptor given by user!\n");
    return STATUS_FAILURE;
  }
  
  //how many employees are we reading
  int count = dbhdr->count;

  struct employee_t *employees = calloc(count, sizeof(struct employee_t));
  if (employees == -1){
    printf("Malloc failed\n");
    return STATUS_FAILURE;
  }

  read(fd, employees, count*sizeof(struct employee_t));

  int i = 0;

  for (; i < count; i++) {
    employees[i].hours = ntohl(employees[i].hours);
  }

  *employeeOut = employees;
  return STATUS_SUCCESS;
}


int create_db_header(int fd, struct db_header_t **headerOut) {
  struct db_header_t *header = calloc(1, sizeof(struct db_header_t));
  if (header == -1) {
    printf("calloc failed to create db header!!\n");
    return STATUS_FAILURE;
  }
  header->magic = HEADER_MAGIC;
  header->count = 0;
  header->version = 0x1;
  header->filesize = sizeof(struct db_header_t);
  
  *headerOut = header;

  return STATUS_SUCCESS;
}

int validate_db_header(int fd, struct db_header_t **headerOut) {
  if (fd < 0) {
    printf("Invalid file descriptor given by user!\n");
    return STATUS_FAILURE;
  }

  struct db_header_t *header = calloc(1, sizeof(struct db_header_t));
  if (header == -1) {
    printf("Calloc failed in validate_db_header() call\n");
    return STATUS_FAILURE;
  }

  if (read(fd, header, sizeof(struct db_header_t)) != sizeof(struct db_header_t)) {
    perror("read");
    free(header);
    return STATUS_FAILURE;
  }

  header->version = ntohs(header->version);
  header->count = ntohs(header->count);
  header->magic = ntohl(header->magic);
  header->filesize = ntohl(header->filesize);

  if (header->magic != HEADER_MAGIC) {
    printf("Improper header magic\n");
    free(header);
    return -1;
  }

  if (header->version != 1) {
    printf("Improper header version\n");
    free(header);
    return -1;
  }
  
  //get meta data from stat library to compare db size to a proper db header size
  struct stat dbstat = {0};
  fstat(fd, &dbstat);
  if (header->filesize != dbstat.st_size) {
    printf("Corrupted data base\n");
    free(header);
    return -1;
  }
  *headerOut = header;

}

void output_file(int fd, struct db_header_t *dbhdr)  {
  if (fd < 0) {    printf("Bad FD from the user \n");
    exit(EXIT_FAILURE);
    }
  dbhdr->version = htons(dbhdr->version);
  dbhdr->count = htons(dbhdr->count);
  dbhdr->magic = htonl(dbhdr->magic);
  dbhdr->filesize = htonl(dbhdr->filesize);

  lseek(fd, 0, SEEK_SET);
  write(fd, dbhdr, sizeof(struct db_header_t));

  return;
} 

 


