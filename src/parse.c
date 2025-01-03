#include <unistd.h>
#include <stdio.h>
<<<<<<< HEAD
#include "parse.h"
=======
#include <stdlib.h>
#include <arpa/inet.h>  
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include "../include/parse.h"
#include "../include/status.h"
>>>>>>> e233001 (Added rd_employee and add_employee functions)

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



