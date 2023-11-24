#include "libmx.h"

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *a, void *b)) {

    if (cmp == NULL || lst == NULL){
        return lst;
    }

    t_list *curr = lst;
    int count = 0;

    while (curr) {
        curr = curr -> next;
        count++;
    }

    for (int i = 0; i < count; i++) {
        curr = lst;
    
    	for (int j = 0; j < count - 1; j++) {
            if (cmp(curr -> data, curr -> next -> data)) {
                void *data = curr -> data; 
                curr -> data = curr -> next -> data; 
                curr -> next -> data = data;     
            }
            curr = curr -> next;
        }
    }

    return lst;
}

