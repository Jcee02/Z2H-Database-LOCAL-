#ifndef PARSE_H
#define PARSE_H

struct db_header_t {
  unsigned short version;
  unsigned short count;
};


int parse_database_header(int, int*);

#endif
