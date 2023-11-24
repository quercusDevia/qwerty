#include "libmx.h"

void mx_push_back(t_list **list, void *data){
    if(*list == NULL || list == NULL){
        *list = mx_create_node(data);
	return;
    }

    t_list *new_n = *list;
    while(new_n->next){
        new_n = new_n->next;
    }
    
    new_n->next = mx_create_node(data);
}

