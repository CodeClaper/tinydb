#include "misc.h"  
#include <stdio.h>
#include <stdlib.h>

// Print out fatal messages.
void fatal(char *s) {
    fprintf(stderr, "%s\n", s);
    exit(EXIT_FAILURE);
}

void fatals(char *s1, char *s2) {
    fprintf(stderr, "%s:%s\n", s1, s2);
    exit(EXIT_FAILURE);
}

void fatald(char *s, int d) {
    fprintf(stderr, "%s:%d\n", s, d);
    exit(EXIT_FAILURE);
}

void fatac(char *s, int c) {
    fprintf(stderr, "%s:%c\n", s, c);
    exit(EXIT_FAILURE);
}

void error_malloc(int line) {
    fprintf(stderr, "Allocate memory error, in line %d.\n", line);
    exit(EXIT_FAILURE);
}
