#ifndef PARSE_H
#define PARSE_H

struct db_header_t {
  unsigned short version;
  unsigned short count;
};


<<<<<<< HEAD
int parse_database_header(int, int*);
=======

struct employee_t {
  char name[256];
  char addr[256];
  unsigned int hours;
};

int create_db_header(int fd, struct db_header_t **headerOut);
int validate_db_header(int fd, struct db_header_t **headerOut);
// employee_t** is a heap-allocated employee buffer we are writing to -> main
int rd_employees(int fd, struct db_header_t *, struct employee_t **);
int add_employee(struct db_header_t*, struct employee_t*, char* addstring);
void output_file(int fd, struct db_header_t *);
>>>>>>> e233001 (Added rd_employee and add_employee functions)

#endif
