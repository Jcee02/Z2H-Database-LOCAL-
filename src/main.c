#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/file.h"
#include "../include/parse.h"


<<<<<<< HEAD
=======
#define OPSTR "nf:a:"

>>>>>>> e233001 (Added rd_employee and add_employee functions)
void print_usage(char**);

int main(int argc, char *argv[]){
    
    char *filepath = NULL;
    char *addstring = NULL;
    bool newfile = false;
    int c;
<<<<<<< HEAD

    while ((c = getopt(argc, argv, "nf:")) != -1) {
=======
    
    int dbfd = -1;
    struct db_header_t *dbhdr = NULL;
    struct employee_t *employees = NULL;
    while ((c = getopt(argc, argv, OPSTR)) != -1) {
>>>>>>> e233001 (Added rd_employee and add_employee functions)
        switch(c){
            case 'n':
                newfile = true;
                break;
            case 'f':
                filepath = optarg;
            case 'a':
                addstring = optarg;
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
        return EXIT_SUCCESS;
    }

<<<<<<< HEAD
    printf("Newfile: %d\n", newfile);
    printf("File path: %s\n", filepath); 
    
=======
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
        employees = realloc(employees, dbhdr->count*sizeof(struct employee_t));
        add_employee(dbhdr, employees, addstring);
    }
    output_file(dbfd, dbhdr);

>>>>>>> e233001 (Added rd_employee and add_employee functions)
    return EXIT_SUCCESS;
}


void print_usage(char *argv[]) {
      printf("Usage: %s -n -f <database file>\n", argv[0]);
      printf("\t -n   - create new database file\n");
      printf("\t -f   - (required) path to database file\n");
      return;
}
