#include "libmx.h"

void mx_pop_front(t_list **head){
    if(head == NULL|| *head == NULL){
        return;
    }

    t_list *front_f = *head;

   *head = front_f->next;

   free(front_f);
   front_f = NULL;
}

