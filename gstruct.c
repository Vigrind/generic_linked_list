#include "gstruct.h"

Node *listNewNode(void *_data, size_t _data_size) {
	Node *newPtr = (Node *)malloc(sizeof(Node));
	if(newPtr == NULL) {
		fprintf(stderr,"No memory aviable\n");
		exit(EXIT_FAILURE);
	}
	newPtr->data = malloc(sizeof(_data_size));
	newPtr->nextPtr = NULL;
	newPtr->prevPtr = NULL;

	//Copy _data to data, 1 byte at step
	for (size_t offset = 0; offset < _data_size; ++offset) {
		*(__uint8_t *)(newPtr->data + offset) = *(__uint8_t *)(_data + offset);
	}

	return newPtr;
}

void listInsertAtFront(Node **_top, Node** _tail ,Node *_node, size_t *size) {
	_node->prevPtr = NULL;
	_node->nextPtr = *_top;
 	Node **res = *_top == NULL ? &(*_tail) : &((*_top)->prevPtr);
	*res = _node;
	*_top = _node;
	++(*size);

	// if(*_top == NULL) 
	// 	*_tail = _node;
	// else
	// 	(*_top)->prevPtr = _node;
}

void *listTop(const Node *_top) {
	if(_top != NULL)
		return _top->data;
	else
		fprintf(stderr,"The list is empty\n");
	exit(EXIT_FAILURE);
}

void listSearchNDelete(Node **_top, Node **_tail, void *_data, size_t _size) {
	while((*_top) != NULL) {
		if(equalData((*_top)->data,_data,_size)) {
			Node *tmp = *_top;	//node to delete
			if(*_top == *_tail) {//control if the list have one element
				free(tmp->data);
				free(tmp);
				*_top = NULL;
				*_tail = NULL;
				return ;
			}
			if((*_top)->prevPtr != NULL && (*_top)->nextPtr != NULL) {//if the element is between two node
				(*_top)->nextPtr->prevPtr = (*_top)->prevPtr;
				(*_top)->prevPtr->nextPtr = (*_top)->nextPtr;
			}else if((*_top)->prevPtr == NULL) {//if is the first element
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

bool equalData(const void* _curr, const void* _data, size_t _d_size) {
	for (size_t offset= 0; offset < _d_size; ++offset)
	{
		if( *(__uint8_t *)(_curr + offset) != *(__uint8_t *)(_data + offset)) //compare byte by byte
			return false;
	}
	return true;
}

void listPrintNode(Node *_top, void (*your_print)(const void *)) {
	while(_top != NULL) {
		(*your_print)(_top->data);
		_top = _top->nextPtr;
	}
	printf("NULL\n");
}

void listDelete(Node **_top, Node **_tail) {
	while (*_top != NULL)
	{
		Node *tmp = (*_top);
		free((*_top)->data);	//first delete memory allocate for pointer to void
		(*_top)->data = NULL;
		*_top = (*_top)->nextPtr;
		free(tmp);				//afeter delete the node
	}
	*_top = NULL;
	*_tail = NULL;
}

function _all = {
	.newNode=&listNewNode,
	.insertAtFront=&listInsertAtFront,
	.top=&listTop,
	.delete=&listDelete,
	.print=&listPrintNode,
	.searchNDelete=&listSearchNDelete,
};

List *newList(){
	List *l = (List*)malloc(sizeof(List));
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
	l->fun = &_all;
	return l;
}