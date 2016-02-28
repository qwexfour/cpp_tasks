#ifndef LIST_LIB
#define LIST_LIB

typedef struct data
{
    int value;
}data_struct_t;

typedef struct list
{
    struct list *next;
    data_struct_t *data;
}list_struct_t;

namespace listlib
{
    void reverseList( list_struct_t *&list );
    void addNode( list_struct_t *&list, data_struct_t *data );
    void printList( list_struct_t *list );
    void deleteList( list_struct_t *list );
}

#endif

