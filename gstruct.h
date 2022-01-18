#ifndef G_STRUCT_HPP
#define G_STRUCT_HPP

#include <stdio.h>
#include <stdlib.h>

/**
 * @enum _bool
 * @brief enum for use true and false
 * 		  instead of 1 and 0
 */
typedef enum _bool {
	false,
	true
}bool;

typedef struct generic_node{
	void *data;	/**< void *data for use every primitive type */
	struct generic_node *nextPtr;
	struct generic_node *prevPtr;
}Node;

typedef struct function_list{
	Node *(*newNode)(void*,size_t);
	void (*insertAtFront)(Node**,Node**,Node*,size_t*);
	void *(*top)(const Node*);
	void (*delete)(Node**,Node**);
	void (*print)(Node*, void (*f_yprint)(const void*));
	void (*searchNDelete)(Node**, Node**, void*, size_t);
}function;

typedef struct generic_list{
	size_t size;
	Node *head;
	Node *tail;
	function *fun;
}List;

#define _insertAtFront(curr,node) curr->fun->insertAtFront(&curr->head,&curr->tail,node,&curr->size)
#define _newNode(curr,elem) curr->fun->newNode(&elem,sizeof(elem))
#define _top(curr) curr->fun->top(curr->head);
#define _delete(curr) curr->fun->delete(&curr->head,&curr->tail);
#define _print(curr,func) curr->fun->print(curr->head,func);
#define _searchNDelete(curr,elem) curr->fun->searchNDelete(&curr->head,&curr->tail,&elem,sizeof(elem))

Node *listNewNode(void *_data, size_t _data_size);
void listInsertAtFront(Node **_top, Node **_tail, Node *_node, size_t *size);
void *listTop(const Node *_top);
void listDelete(Node **_top, Node **_tail);
void listSearchNDelete(Node **_top, Node **_tail, void *_data, size_t _size);
void listPrintNode(Node* _top, void (*your_print)(const void *));
void listInsertAtBack(Node **_top, Node **_tail, Node *_node, size_t *size);
bool equalData(const void* _curr, const void* _data,size_t _d_size);

List *newList();
#endif