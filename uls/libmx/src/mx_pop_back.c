#include "libmx.h"

void mx_pop_back(t_list **head){
    if(head == NULL || *head == NULL){
        return;
    }

    if((*head)->next == NULL){
        free(*head);
	*head = NULL;
	return;
    }

    t_list *temp_n = *head;

    while(temp_n->next->next != NULL){
        temp_n = temp_n->next;
    }

    free(temp_n->next);
    temp_n->next = NULL;
    temp_n = NULL;
}

