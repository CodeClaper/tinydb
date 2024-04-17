#include "data.h"

/* Create List and initialization. 
 * Return the created list.
 * */
List *create_list();


/* Append item to list. 
 * Return current number of items in list.
 * */
int append_list(List *list, void *item);


/* Append item to list at index. 
 * Return the index of the new item in list.
 * Return -1 if fail.
 * */
int append_at(List *list, void *item, int index);


/* Destroy list. */
void destroy_list(List *list);
