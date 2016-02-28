#include"listlib.h"
#include<iostream>






void listlib::reverseList( list_struct_t *&list )
{
    if( list == NULL )
        return;
    list_struct_t *nextNode = list->next, *nextNodeCopy = NULL;
    list_struct_t *currentNode = list, *currentNodeCopy = NULL;
    list_struct_t *previousNode = NULL, *previousNodeCopy = NULL;
    while( currentNode != NULL )
    {
        nextNodeCopy = nextNode;
        currentNodeCopy = currentNode;
        previousNodeCopy = previousNode;
        nextNode = ( nextNodeCopy == NULL ) ? NULL : nextNodeCopy->next;
        currentNode = nextNodeCopy;
        previousNode = currentNodeCopy;
        //
        currentNodeCopy->next = previousNodeCopy;
    }
    list = currentNodeCopy;
    return;
}

void listlib::addNode( list_struct_t *&list, data_struct_t *data )
{
    list_struct_t *newNode = new list_struct_t;
    newNode->next = list;
    newNode->data = data;
    list = newNode;
    return;
}



void listlib::printList( list_struct_t *list )
{
    if( list == NULL )
        return;
    list_struct_t *currentNode = list;
    while( currentNode != NULL )
    {
        std::cout << currentNode->data->value << std::endl;
        currentNode = currentNode->next;
    }
    return;
}

void listlib::deleteList( list_struct_t *list )
{
    if( list == NULL )
        return;
    list_struct_t *currentNode = list, *tmp = NULL;
    while( currentNode != NULL )
    {
        tmp = currentNode->next;
        //std::cout << currentNode << std::endl;
        delete currentNode;
        currentNode = tmp;
    }
    return;
}

