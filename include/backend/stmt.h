#include "data.h"

/* Execute statement
 * Now supported statments:
 * (1) SELECT
 * (2) UPDATE
 * (3) Insert
 * (4) DELETE
 * (5) CREATE TABLE
 * (6) SHOW TABLES AND SHOW MEMORY
 * (7) DESCRIBE TABLE
 * (8)  BEGIN TRANSACTION
 * (9)  COMMIT TRANSACTION
 * (10) ALTER TABLE ADD or DROP COLUMN.
 * */
void Execute(char *sql);
