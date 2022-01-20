#ifndef G_STRUCT_HPP
#define G_STRUCT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @enum _bool
 * @brief enum for use true and false
 * 		  instead of 1 and 0
 */
typedef enum _bool {
	true = 1,
	false = 0
}bool;

typedef struct generic_node{
	void *data;	/**< void *data for use every primitive type */
	struct generic_node *nextPtr;
	struct generic_node *prevPtr;
}Node;

typedef struct generic_list{
	//size_t type_size;
	size_t size;
	Node *head;
	Node *tail;
}List;

void my_move(void* _dst, const void* _src, size_t _size);
Node *new_node(void *_data, size_t _data_size);
void insert_at_front(List *_list, Node *_node);
void insert_at_back(List *_list, Node *_node);
void insert_in_order(List *_list, Node *_node, bool (*compare)(const void*,const void*)); //da inserire nel dock
void delete(List *_list);
void search_delete(List *_list, void *_data, bool (*equal)(const void*, const void*));
void *top(const List *_list);
void print_list(const List* head, void (*your_print)(const void *));
List *newList();
#endif