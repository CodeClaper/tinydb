#include "data.h"

/*Get table from statement*/
Table *get_statement_table(Statement *stmt);

/* Execute statement
 * Now supported statments:
 * (1) SELECT
 * (2) UPDATE
 * (3) Insert
 * (4) DELETE
 * (5) CREATE TABLE
 * (6) SHOW TABLES AND SHOW MEMORY
 * (7) DESCRIBE TABLE
 * */
ExecuteResult statement(char *sql);
