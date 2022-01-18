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

Node *list_new_node(void *_data, size_t _data_size) {
	Node *newPtr = (Node *)malloc(sizeof(Node));
	if(newPtr == NULL) {
		fprintf(stderr,"No memory aviable\n");
		exit(EXIT_FAILURE);
	}
	newPtr->data = malloc(_data_size);
	newPtr->nextPtr = NULL;
	newPtr->prevPtr = NULL;
	my_move(newPtr->data,_data,_data_size);
	//memmove(newPtr->data,_data,_data_size); //we can use also memmove

	return newPtr;
}

void list_insert_at_front(Node **_top, Node** _tail ,Node *_node, size_t *_size) {
	_node->prevPtr = NULL;
	_node->nextPtr = *_top;
	Node **res = *_top == NULL ? &(*_tail) : &((*_top)->prevPtr);
	*res = _node;
	*_top = _node;
	++(*_size);

	// if(*_top == NULL) 
	// 	*_tail = _node;
	// else
	// 	(*_top)->prevPtr = _node;
}

void list_insert_at_back(Node **_top, Node **_tail, Node *_node, size_t *_size) {
	_node->nextPtr = NULL;
	_node->prevPtr = *_tail;
	Node **res = *_tail == NULL ? &(*_top) : &((*_tail)->nextPtr);
	*res = _node;
	*_tail = _node;
	++(*_size);
}

void *list_top(const Node *_top) {
	if(_top != NULL)
		return _top->data;
	else
		fprintf(stderr,"The list is empty\n");
	exit(EXIT_FAILURE);
}

void list_search_delete(Node **_top, Node **_tail, void *_data, size_t _size, size_t *_lsize) {
	while((*_top) != NULL) {
		if(equal_data((*_top)->data,_data,_size)) {
			--(*_lsize);
			Node *tmp = *_top;	//node to delete
			if(!(*_top)->prevPtr && !(*_top)->nextPtr) {//control if the list have one element
				free(tmp->data);
				free(tmp);
				*_top = NULL;
				*_tail = NULL;
				return ;
			}
			if((*_top)->prevPtr  && (*_top)->nextPtr ) {//if the element is between two node
				(*_top)->nextPtr->prevPtr = (*_top)->prevPtr;
				(*_top)->prevPtr->nextPtr = (*_top)->nextPtr;
			}else if(!(*_top)->prevPtr) {//if is the first element
				*_top = (*_top)->nextPtr;
				(*_top)->prevPtr = NULL;
			}else {//if is the last element
				*_tail = (*_top)->prevPtr;
				(*_top)->prevPtr->nextPtr = NULL;
			}
			free(tmp->data);
			free(tmp);
			return;
		}
		_top = &(*_top)->nextPtr;
	}
	printf("No element is found\n");
}

bool equal_data(const void* _curr, const void* _data, size_t _d_size) {
	__uint8_t *t_data = (__uint8_t*)_curr;
	__uint8_t *o_data = (__uint8_t*)_data;
	for (size_t offset= 0; offset < _d_size; ++offset)
	{
		if(t_data[offset] != o_data[offset]) //compare byte by byte
			return false;
	}
	return true;
}

void list_print_node(Node *_top, void (*your_print)(const void *)) {
	while(_top != NULL) {
		(*your_print)(_top->data);
		_top = _top->nextPtr;
	}
	printf("NULL\n");
}

void list_delete(Node **_top, Node **_tail, size_t *_lsize) {
	while (*_top != NULL)
	{
		Node *tmp = (*_top);
		free((*_top)->data);	//first delete memory allocate for pointer to void
		(*_top)->data = NULL;
		*_top = (*_top)->nextPtr;
		free(tmp);				//afeter delete the node
	}
	*_lsize = 0;
	*_top = NULL;
	*_tail = NULL;
}

function _all = {
	.newNode=&list_new_node,
	.insertAtFront=&list_insert_at_front,
	.insertAtBack=&list_insert_at_back,
	.top=&list_top,
	.delete=&list_delete,
	.print=&list_print_node,
	.searchNDelete=&list_search_delete
};

List *newList(){
	List *l = (List*)malloc(sizeof(List));
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
	l->fun = &_all;
	return l;
}