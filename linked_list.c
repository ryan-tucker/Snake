#include <stdlib.h>
#include <stdio.h>
#include "linked_list.h"
/*Doubly Linked List implementation (for int) */
List *create_list() {
    List *temp = malloc(sizeof(List));
    temp->head = NULL;
    temp->tail = NULL;
    return temp;
}

void delete_list(List *list) {
    if (list != NULL && list->head != NULL) {
        delete_nodes(list->head);
        free(list);
    }
}

void append(List *list, int x, int y) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Failed memory allocation");
    }

    new_node->x = x;
    new_node->y = y;
    new_node->next = NULL;    

    if(list->head == NULL) {
        new_node->previous = NULL;
        list->head = new_node;
        list->tail = new_node;
        return ;
    }

    list->tail->next = new_node;
    new_node->previous = list->tail;
    list->tail = new_node;
}

void push(List *list, int x, int y) {
    Node *new_node = malloc(sizeof(Node));
    new_node->x = x;
    new_node->y = y;
    new_node->previous = NULL;
    new_node->next = list->head;
    if(list->head != NULL) {
        list->head->previous = new_node;
    } else {
        list->tail = new_node;
    }
    list->head = new_node;
}

/*Deletes recursively because it's kind of cool, however since we have a tail
it's unnecessary and probably slower than iterating from the tail.*/
void delete_nodes(Node *head_node) {
    if (head_node->next == NULL) {
        free(head_node);
    } else {
        delete_nodes(head_node->next);
        free(head_node);
    }
}
/*WARNING: Free's memory associated with the tail node as well as removes it
 * from the list*/
void delete_tail(List *list) {
        if (list->tail->previous != NULL) {
            list->tail->previous->next = NULL;
        }
        Node *to_remove = list->tail;
        if (to_remove != NULL) {
           list->tail = list->tail->previous;
           free(to_remove);
        }
}
