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

typedef struct function_list function;

typedef struct generic_list{
	size_t size;
	Node *head;
	Node *tail;
	function *fun;
}List;

struct function_list{
	bool (*equalData)(const void*,const void*); /**< If you want, you can save your equal function in the structure */
	bool (*comp)(const void*,const void*); /**< If you want, you can save your compare function in the structure */
	Node *(*newNode)(void *, size_t);
	void (*insertAtFront)(List *, Node *);
	void (*insertAtBack)(List *, Node *);
	void (*insertInOrder)(List *, Node *, bool (*compare)(const void*,const void*));
	void *(*top)(const Node*);
	void (*delete)(List *);
	void (*print)(Node*, void (*f_yprint)(const void*));
	void (*searchNDelete)(List *, void *, bool (*equal)(const void*, const void*));
};

void my_move(void* _dst, const void* _src, size_t _size);

Node *list_new_node(void *_data, size_t _data_size);

void list_insert_at_front(List *_list, Node *_node);
void list_insert_at_back(List *_list, Node *_node);
void list_insert_in_order(List *_list, Node *_node, bool (*compare)(const void*,const void*)); //da inserire nel dock


void list_delete(List *_list);
void list_search_delete(List *_list, void *_data, bool (*equal)(const void*, const void*));

void *list_top(const Node *_top);
void list_print_node(Node* _top, void (*your_print)(const void *));
List *newList();
#endif