#include"listlib.h"
#include<iostream>



int main()
{
    const int N = 15;

    data_struct_t data[N] = {};
    for( int i = 0; i < N; i++ )
        data[i].value = i;
    list_struct_t *list = new list_struct_t;
    list->next = NULL;
    list->data = &data[0];
    for( int i = 1; i < N; i++ )
        listlib::addNode( list, &(data[i]) );
    std::cout << "Straight:" << std::endl;
    listlib::printList( list );
    listlib::reverseList( list );
    std::cout << "Reversed:" << std::endl;
    listlib::printList( list );
    listlib::deleteList( list );
    return 0;
}
