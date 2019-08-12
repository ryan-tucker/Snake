#ifndef LINKED_LIST
#define LINKED_LIST

typedef struct Node{
    int x;
    int y;
    struct Node *next;
    struct Node *previous;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

void append(List *list, int x, int y);

void push(List *list, int x, int y);

void delete_nodes(Node *head_node);

void delete_tail(List *list);

#endif
