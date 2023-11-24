#include "libmx.h"

void mx_push_front(t_list **list, void *data){
    if(*list == NULL || list == NULL){
        *list = mx_create_node(data);
	return;
    }

    t_list *new_n = mx_create_node(data);
    new_n->next = *list;
    *list = new_n;
}

