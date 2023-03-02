#ifndef G_STRUCT_HPP
#define G_STRUCT_HPP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_function;

enum _bool {
	true = 1,
	false = 0
};
typedef enum _bool bool;

struct generic_node{
	void *data;
	struct generic_node *nextPtr;
	struct generic_node *prevPtr;
};
typedef struct generic_node Node;


struct generic_list{
	struct list_function *functions;
	size_t type_size;
	size_t list_size;
	Node *head;
	Node *tail;
};
typedef struct generic_list List;


struct list_function {
	Node *(*new_node)(void*, const List*);
	void (*insert_at_front)(List*, Node*);
	void (*insert_at_back)(List*, Node*);
	void (*insert_in_order)(List*, Node*, bool (*compare)(const void*, const void*));
	void (*search_delete)(List*, void*, bool (*equal)(const void*, const void*));
	void *(*top)(const List*);
	void *(*tail)(const List*);
	void *(*top_and_delete)(List*);
	void *(*tail_and_delete)(List*);
	void (*print)(const List*, void (*your_print)(const void *));
	bool (*equal)(const List*, const List*, bool (*equal)(const void*, const void*));
	void (*copy_list)(List *, const List *);
	List *(*create_third_list)(List*, List*, size_t, void *(*fun)(void*,void*));
};
typedef struct list_function Functions;

#define __private static
#define new_list(size_type)								list_init(size_type)
#define n_node(val, list)								list->functions->new_node(&val, list)
#define insert_order(list, val, comp_function)			list->functions->insert_in_order(list, n_node(val, list), comp_function);
#define insert_front(list, val)							list->functions->insert_at_front(list, n_node(val, list))
#define insert_back(list, val)							list->functions->insert_at_back(list, n_node(val, list))
#define l_print(list, print_function)					list->functions->print(list, print_function)
#define search_and_delete(list, val, equal_function)	list->functions->search_delete(list, &val, equal_function)

void list_delete(List *list);
List *list_init(size_t type);

#endif