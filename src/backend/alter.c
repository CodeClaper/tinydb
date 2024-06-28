#include <stdbool.h>
#include "data.h"
#include "alter.h"
#include "check.h"

/* Try to catpture table.
 * If these other session on the table, wait and test. 
 * */
static bool capture_table(char *table_name) {
    return true;
}

/* Convert ColumnDefNode to MetaColumn. */
static MetaColumn *convert_meta_column(ColumnDefNode *column_def, char *table_name) {

}

/* Add new Column. */
static void add_new_column(AddColumnDef *add_column_def, char *table_name, DBResult *result) {
    if (capture_table(table_name)) {
        
    }
}


/* Execute alter table statement. */
void exec_alter_statement(AlterTableNode *alter_table_node, DBResult *result) {
    if (check_alter_table(alter_table_node)) {
        AlterTableAction *alter_table_action = alter_table_node->action;
        switch (alter_table_action->type) {
            case ALTER_TO_ADD_COLUMN:
                add_new_column(alter_table_action->action.add_column, 
                               alter_table_node->table_name, result);
                break;
            case ALTER_TO_DROP_COLUMN:
                break;
            case ALTER_TO_CHANGE_COLUMN:
                break;
        }
    }
}
