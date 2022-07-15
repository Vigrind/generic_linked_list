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
Node *list_new_node(void *data, const List* l);
void list_insert_at_front(List *list, Node *node);
void list_insert_at_back(List *list, Node *node);
void list_insert_in_order(List *list, Node *node, bool (*compare)(const void*,const void*));
void list_delete(List *list);
void list_search_delete(List *list, void *data, bool (*equal)(const void*, const void*));
void *list_top(const List *list);
void *list_tail(const List *list);
void *list_top_and_delete(List *list);
void *list_tail_and_delete(List *list);
void list_print(const List *list, void (*your_print)(const void *));
bool list_equal(const List *_first, const List* _second, bool (*equal)(const void*, const void*));
List *list_create(size_t _type);
void list_copy_list(List *dst_list, const List *src_list);
List *list_create_third_list(List *_f, List *_s, size_t _type,void *(*fun)(void*,void*));
#endif