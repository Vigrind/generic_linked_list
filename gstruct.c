#include "gstruct.h"

//Copy _src to _dst, 1 byte at step
void my_move(void* _dst, const void* _src, size_t _size) {
	//__uint8_t size is 1 byte (8 bit)
	__uint8_t *t_data = (__uint8_t*)_dst;
	__uint8_t *o_data = (__uint8_t*)_src;
	for (size_t offset = 0; offset < _size; ++offset) {
		t_data[offset] = o_data[offset];
	}
}

Node *new_node(void *_data, size_t _data_size) {
	Node *newPtr = (Node *)malloc(sizeof(Node));
	if(newPtr == NULL) {
		fprintf(stderr,"No memory aviable\n");
		exit(EXIT_FAILURE);
	}
	newPtr->data = malloc(_data_size);
	newPtr->nextPtr = NULL;
	newPtr->prevPtr = NULL;
	my_move(newPtr->data,_data,_data_size);
	//memmove(newPtr->data,_data,_data_size); //we can also use memmove

	return newPtr;
}

void insert_at_front(List *_list, Node *_node) {
	_node->prevPtr = NULL;
	_node->nextPtr = _list->head;
	Node **res = _list->head == NULL ? &(_list->tail) : &(_list->head->prevPtr);
	*res = _node;
	_list->head = _node;
	_list->size++;

	// if(_list->head == NULL) 
	// 	_list->tail = _node;
	// else
	// 	(_list->head)->prevPtr = _node;
}

void insert_at_back(List *_list, Node *_node) {
	_node->nextPtr = NULL;
	_node->prevPtr = _list->tail;
	Node **res = _list->tail == NULL ? &(_list->head) : &(_list->tail->nextPtr);
	*res = _node;
	_list->tail = _node;
	_list->size++;
}

void insert_in_order(List *_list, Node *_node, bool (*compare)(const void*,const void*)) {
	if(!_list->head) //if is the first element of the list
		insert_at_front(_list,_node);
	else {
		Node *curr = _list->head;
		while (curr != NULL && (*compare)(_node->data,curr->data)) {
			curr = curr->nextPtr;
		}
		if(!curr) //if is the last element of the list
			insert_at_back(_list,_node);
		else { //insert between two node
			_node->nextPtr = curr;
			_node->prevPtr = curr->prevPtr;
			Node **res = _list->head == curr ? &(_list->head) : &(curr->prevPtr->nextPtr); //if insert at the first element of the list
			*res = _node;
			curr->prevPtr = _node;
		}
	}
}

void *top(const List* _list) {
	if(_list->head != NULL)
		return _list->head->data;
	else
		fprintf(stderr,"The list is empty\n");
	exit(EXIT_FAILURE);
}

void search_delete(List *_list, void *_data, bool (*equal)(const void*, const void*)) {
	Node *curr = _list->head;
	while(curr != NULL) {
		Node *next = curr->nextPtr; //save next because curr will be delete 
		if((*equal)(curr->data,_data)) {
			Node *tmp = curr;	//node to delete
			_list->size--;
			if(!curr->prevPtr && !curr->nextPtr) {//control if the list have one element
				free(tmp->data);
				free(tmp);
				_list->head = NULL;
				_list->tail = NULL;
				return ;
			}
			if(curr->prevPtr  && curr->nextPtr ) {//if the element is between two node
				curr->nextPtr->prevPtr = curr->prevPtr;
				curr->prevPtr->nextPtr = curr->nextPtr;
			}else if(!curr->prevPtr) {//if is the first element
				_list->head = curr->nextPtr;
				curr->nextPtr->prevPtr = NULL;
			}else {//if is the last element
				_list->tail = curr->prevPtr;
				curr->prevPtr->nextPtr = NULL;
			}
			free(tmp->data);
			free(tmp);
		}
		curr = next;
	}
}

void print_list(const List *_list, void (*your_print)(const void *)) {
	Node *tmp = _list->head;
	while(tmp != NULL) {
		(*your_print)(tmp->data);
		tmp = tmp->nextPtr;
	}
	printf("NULL\n");
}

void delete(List *_list) {
	while (_list->head != NULL)
	{
		Node *tmp = (_list->head);
		free((_list->head)->data);	//first delete memory allocate for pointer to void
		(_list->head)->data = NULL;
		_list->head = (_list->head)->nextPtr;
		free(tmp);				//afeter delete the node
	}
	_list->size = 0;
	_list->head = NULL;
	_list->tail = NULL;
}

List *newList(){
	List *l = (List*)malloc(sizeof(List));
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
	return l;
}