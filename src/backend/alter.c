#include <stdbool.h>
#include "data.h"
#include "alter.h"
#include "mmu.h"
#include "check.h"
#include "table.h"
#include "cache.h"
#include "buffer.h"
#include "create.h"
#include "utils.h"
#include "log.h"

/* Try to catpture table.
 * If these other session on the table, wait and test. 
 * */
static void capture_table(char *table_name) {
}

/* Release Table. */
static void release_table(char *table_name) {
    clear_table_cache(table_name);
    clear_table_buffer(table_name);
}

/* Add new Column. */
static void add_new_column(AddColumnDef *add_column_def, char *table_name, DBResult *result) {
    /* Capture table exclusively. */
    capture_table(table_name);
    MetaColumn *new_meta_column = combine_user_meta_column(add_column_def->column_def, table_name);        
    if (add_new_meta_column(table_name, new_meta_column, add_column_def->position_def)) {
        result->success = true;
        result->message = format("Add column '%s' for table '%s' successfully.", 
                                 new_meta_column->column_name, 
                                 table_name);
        db_log(SUCCESS, "Add column '%s' for table '%s' successfully.", 
               new_meta_column->column_name, 
               table_name);
    }
    /* Release table. */
    release_table(table_name);
}

/* Drop old column. */
static void drop_old_column(DropColumnDef *drop_column_def, char *table_name, DBResult *result) {

}

/* Change old column. */
static void change_old_column(ChangeColumnDef *change_column_def, char *table_name, DBResult *result) {

}


/* Execute alter table statement. */
void exec_alter_statement(AlterTableNode *alter_table_node, DBResult *result) {
    if (check_alter_table(alter_table_node)) {
        AlterTableAction *alter_table_action = alter_table_node->action;
        switch (alter_table_action->type) {
            case ALTER_TO_ADD_COLUMN:
                add_new_column(alter_table_action->action.add_column, alter_table_node->table_name, result);
                break;
            case ALTER_TO_DROP_COLUMN:
                drop_old_column(alter_table_action->action.drop_column, alter_table_node->table_name, result);
                break;
            case ALTER_TO_CHANGE_COLUMN:
                change_old_column(alter_table_action->action.change_column, alter_table_node->table_name, result);
                break;
        }
    }
}
