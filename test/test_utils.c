#include "../utils.h"
#include <stdio.h>

int main() {
    char *p = replace("student.dbt", ".dbt", "S");
    printf("%s\n", p);
}
