#include "data.h"

// Equal operation.
bool equal(void *source, void *target, DataType data_type);

// Not equal operation.
bool not_equal(void *source, void *target, DataType data_type);

// Not equal operation.
bool greater(void *source, void *target, DataType data_type);

// Not equal operation.
bool greater_equal(void *source, void *target, DataType data_type);

// Not equal operation.
bool less(void *source, void *target, DataType data_type);

// Not equal operation.
bool less_equal(void *source, void *target, DataType data_type);

// Eval
bool eval(CompareType compare_type, void *source, void *target, DataType data_type);
