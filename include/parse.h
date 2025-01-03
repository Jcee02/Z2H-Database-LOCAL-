#ifndef PARSE_H
#define PARSE_H

#define HEADER_MAGIC 0x4c4c4144

struct db_header_t {
  unsigned int magic;  
  unsigned short version;
  unsigned short count;
  unsigned int filesize;
};

int create_db_header(int fd, struct db_header_t **headerOut);
int validate_db_header(int fd, struct db_header_t **headerOut);
void output_file(int fd, struct db_header_t *);

#endif
