#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/status.h"
#include "../include/file.h"

int create_db_file(char *filename) {
    int fd = open(filename, O_RDWR); 
    if (fd != -1) {
        close(fd);
        printf("File already exists in database\n");
        return STATUS_FAILURE;
    }
    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd == -1) {
        perror("error");
        return STATUS_FAILURE;
    }
    return fd;
}
int open_db_file(char *filename) {
    
    int fd = open(filename, O_RDWR, 0644);
    if (fd == -1) {
        perror("error");
        return STATUS_FAILURE;
    }
    return fd;
}



