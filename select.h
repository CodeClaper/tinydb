#include "data.h"

// generate select reuslt.
SelectResult *gen_select_result(SelectNode *select_node);

// print select result using beauty format.
void print_select_result_beauty(SelectResult *select_result);

// print select result using plain format.
void print_select_result_plain(SelectResult *select_result);
