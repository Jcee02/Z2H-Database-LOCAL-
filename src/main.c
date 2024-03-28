#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/file.h"
#include "../include/parse.h"


void print_usage(char**);

int main(int argc, char *argv[]){
    
    char *filepath = NULL;
    bool newfile = false;
    int c;

    while ((c = getopt(argc, argv, "nf:")) != -1) {
        switch(c){
            case 'n':
                newfile = true;
                break;
            case 'f':
                filepath = optarg;
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

    printf("Newfile: %d\n", newfile);
    printf("File path: %s\n", filepath); 
    
    return EXIT_SUCCESS;
}


void print_usage(char *argv[]) {
      printf("Usage: %s -n -f <database file>\n", argv[0]);
      printf("\t -n   - create new database file\n");
      printf("\t -f   - (required) path to database file\n");
      return;
}
