#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utilities.h"



// Generic linked list implementations
List new_list() {
    List new_list = (List) malloc(sizeof(struct list));
    new_list->size = 0;
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->head->next = new_list->tail;
    return new_list;
}

void add_into(List list, void* data) {
    Node newNode = (Node) malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    
    if(!list->head && !list->tail) list->head = newNode;
    else if (!list->tail) {
        list->tail = newNode;
    }
    else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;
}

void* get_from_list(List list, int nNode) {
    Node current_node =  list->head;
    int iNode = 0;

    if(nNode > list->size) return current_node;

    while (current_node != NULL) {
        if (iNode == nNode) return current_node;
        iNode++;
        current_node = current_node->next;
    }

    return NULL;
}

void destroy(List list) {
    Node current_node = list->head;
    while (current_node != NULL) {
        Node next_node = current_node->next;
        free(current_node);
        current_node = next_node;
    }
    free(list);
}


// Generic dynamic array implementations
void init_array(Array self, size_t selfCapacity) {
    self->size = 0;
    self->capacity = selfCapacity;
    self->array = malloc(selfCapacity);
}

void push_back(Array self, void* newData) {
    self->size++;
    void* startTmp = realloc(self->array, self->capacity * (self->size + 1));
    
    if(!startTmp) {
        printf("Error on realloc");
        exit(3);
    }
    self->array = startTmp;
    memcpy(self->array+(self->capacity * (self->size - 1)), newData, self->capacity);
}

void remove_from_array(Array self, int index) {
    void* tmp = malloc(self->capacity * (self->size - 1));

    if (index != 0) {
        memcpy(tmp, self->array, self->capacity * index);
    }
    if (index != self->size - 1) {
        memcpy(tmp+index, self->array+index+1, self->capacity * (self->size - index - 1));
    }
    self->array = tmp;
}

char control_characters_parsing(char currChar) {
    switch (currChar) {
        case 'n':
            return '\n';
        case 't':
            return '\t';
        case 'r':
            return '\r';
        case 'b':
            return '\b';
        case 'a':
            return '\a';
        default:
            return currChar;
    }
}