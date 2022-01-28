#ifndef G_STRUCT_HPP
#define G_STRUCT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum _bool {
	true = 1,
	false = 0
}bool;

typedef struct generic_node{
	void *data;
	struct generic_node *nextPtr;
	struct generic_node *prevPtr;
}Node;

typedef struct generic_list{
	size_t type_size;
	size_t size;
	Node *head;
	Node *tail;
}List;

void my_move(void* _dst, const void* _src, size_t _size);
Node *new_node(void *_data, const List* _l);
void insert_at_front(List *_list, Node *_node);
void insert_at_back(List *_list, Node *_node);
void insert_in_order(List *_list, Node *_node, bool (*compare)(const void*,const void*));
void delete_list(List *_list);
void search_delete(List *_list, void *_data, bool (*equal)(const void*, const void*));
void *top_list(const List *_list);
void print_list(const List *_list, void (*your_print)(const void *));
bool equal_list(const List *_first, const List* _second, bool (*equal)(const void*, const void*));
List *new_list(size_t _type);
void copy_list(List *_dst_list, const List *_src_list);
List *create_third_list(List *_f, List *_s, size_t _type,void *(*fun)(void*,void*));
#endif