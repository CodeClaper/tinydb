#include "misc.h"  
#include <stdio.h>
#include <stdlib.h>

// Print out fatal messages.
void fatal(char *s) {
    fprintf(stderr, "%s, in line %d\n", s, __LINE__);
    exit(EXIT_FAILURE);
}

void fatals(char *s1, char *s2) {
    fprintf(stderr, "%s:%s, in line %d\n", s1, s2, __LINE__);
    exit(EXIT_FAILURE);
}

void fatald(char *s, int d) {
    fprintf(stderr, "%s:%d, in line %d\n", s, d, __LINE__);
    exit(EXIT_FAILURE);
}

void fatac(char *s, int c) {
    fprintf(stderr, "%s:%c, in line %d\n", s, c, __LINE__);
    exit(EXIT_FAILURE);
}

void error_malloc(int line) {
    fprintf(stderr, "Allocate memory error, in line %d.\n", line);
    exit(EXIT_FAILURE);
}
