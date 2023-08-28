#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "../table.h"
#include "../meta.h"

char *data_dir = "../data/";

int main(void) {

    MetaTable *meta_table = malloc(sizeof(MetaTable));
    meta_table->table_name = "demo";
    meta_table->column_size = 3;
    MetaColumn *col1 = malloc(sizeof(MetaColumn));
    strcpy(col1->column_name, "id");
    col1->column_type = T_INT;
    col1->is_primary = true;
    col1->column_length = 4;
    MetaColumn *col2 = malloc(sizeof(MetaColumn));
    strcpy(col2->column_name, "address");
    col2->column_type = T_STRING;
    col2->column_length = 32;
    col2->is_primary = false;
    MetaColumn *col3 = malloc(sizeof(MetaColumn));
    strcpy(col3->column_name, "ipone");
    col3->column_type = T_STRING;
    col3->column_length = 11;
    col3->is_primary = false;

    for(int i = 0; i < 3; i++) {
        meta_table->meta_column[i] = malloc(sizeof(MetaColumn));
    }
    memcpy(meta_table->meta_column[0], col1, sizeof(MetaColumn));
    memcpy(meta_table->meta_column[1], col2, sizeof(MetaColumn));
    memcpy(meta_table->meta_column[2], col3, sizeof(MetaColumn));
    create_table(meta_table);
    printf("end");
}
