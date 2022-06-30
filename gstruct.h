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

void my_move(void* dst, const void* src, size_t size);
Node *new_node(void *data, const List* l);
void insert_at_front(List *list, Node *node);
void insert_at_back(List *list, Node *node);
void insert_in_order(List *list, Node *node, bool (*compare)(const void*,const void*));
void delete_list(List *list);
void search_delete(List *list, void *data, bool (*equal)(const void*, const void*));
void *top_list(const List *list);
void *tail_list(const List *list);
void *top_and_delete(List *list);
void *tail_and_delete(List *list);
void print_list(const List *list, void (*your_print)(const void *));
bool equal_list(const List *_first, const List* _second, bool (*equal)(const void*, const void*));
List *new_list(size_t _type);
void copy_list(List *dst_list, const List *src_list);
List *create_third_list(List *_f, List *_s, size_t _type,void *(*fun)(void*,void*));
#endif