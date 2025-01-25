#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/file.h"
#include "../include/parse.h"
#include "../include/status.h"

/* n is a boolean flag for new file 
 * f is a data argument (colon) to enter the name of a file (new if -n set up)
 * a is a data argument (colon) to enter new entry to db file 
 * l is a boolean flag for listing all of a db file entries */
#define OPSTR "nf:a:l"

void print_usage(char**);

int main(int argc, char *argv[]){
    
    char *filepath = NULL;
    char *addstring = NULL;
    bool newfile = false;
    bool listing = false;
    int c;
    
    int dbfd = -1;
    struct db_header_t *dbhdr = NULL;
    struct employee_t *employees = NULL;
    while ((c = getopt(argc, argv, OPSTR)) != -1) {
        switch(c){
            case 'n':
                newfile = true;
                break;
            case 'f':
                filepath = optarg;
                break;
            case 'a':
                addstring = optarg;
                break;
            case 'l':
                listing = true;
                break;
            case '?':
                printf("Unknown option -%c\n", c);
                break;
            default:
                return -1;
       }
    }

    if (filepath == NULL) {
        printf("File path is a required argument.\n");
        print_usage(argv);
        exit(EXIT_SUCCESS);
    }

    if (newfile) {
        dbfd = create_db_file(filepath);
        if (dbfd == STATUS_FAILURE) {
            printf("Unable to create database file\n");
            exit(EXIT_FAILURE);
      } 

        if (create_db_header(dbfd, &dbhdr) == STATUS_FAILURE) {
          printf("Unable to create database header\n");
          exit(EXIT_FAILURE);
        }
    } else {
          dbfd = open_db_file(filepath);
          if (dbfd == STATUS_FAILURE) {
              printf("Unable to open database file\n");
              exit(EXIT_FAILURE);
          }
          if (validate_db_header(dbfd, &dbhdr) == STATUS_FAILURE) {
              printf("Failed to validate database header \n");
              exit(EXIT_FAILURE);
          }
      }


    if (rd_employees(dbfd, dbhdr, &employees) != STATUS_SUCCESS) {
        printf("Failed to read employees\n");
        return 0;
    }
    if (addstring) {
        dbhdr->count++;
        employees = realloc(employees, dbhdr->count*(sizeof(struct employee_t)));
        add_employee(dbhdr, employees, addstring);
    }

    if (listing) {
        list_db(dbhdr, employees);
    }
    output_file(dbfd, dbhdr, employees);

    return EXIT_SUCCESS;
}


void print_usage(char *argv[]) {
      printf("Usage: %s [-n] [-f filename]\n", argv[0]);
      printf("\t [-n]   - create new database file\n");
      printf("\t [-f filename]   - (required) path to database file\n");
      return;
} 
