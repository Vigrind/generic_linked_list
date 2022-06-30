#include "gstruct.h"

//Copy src to dst, 1 byte at step
void my_cpy(void* dst, const void* src, size_t size) {
	//__uint8_t size is 1 byte (8 bit)
	__uint8_t *t_data = (__uint8_t*)dst;
	__uint8_t *o_data = (__uint8_t*)src;
	for (size_t offset = 0; offset < size; ++offset) {
		t_data[offset] = o_data[offset];
	}
}

Node *new_node(void *data, const List* list) {
	Node *newPtr = (Node *)malloc(sizeof(Node));
	if(newPtr == NULL) {
		fprintf(stderr,"No memory aviable\n");
		exit(EXIT_FAILURE);
	}
	newPtr->data = malloc(list->type_size);
	newPtr->nextPtr = NULL;
	newPtr->prevPtr = NULL;
	//my_cpy(newPtr->data,data,list->type_size);
	memcpy(newPtr->data,data,list->type_size); //we can also use memcpy
	return newPtr;
}

void insert_at_front(List *list, Node *node) {
	node->prevPtr = NULL;
	node->nextPtr = list->head;
	Node **res = list->head == NULL ? &(list->tail) : &(list->head->prevPtr);
	*res = node;
	list->head = node;
	list->size++;
}

void insert_at_back(List *list, Node *node) {
	node->nextPtr = NULL;
	node->prevPtr = list->tail;
	Node **res = list->tail == NULL ? &(list->head) : &(list->tail->nextPtr);
	*res = node;
	list->tail = node;
	list->size++;
}

void insert_in_order(List *list, Node *node, bool (*compare)(const void*,const void*)) {
	if(!list->head) //if is the first element of the list
		insert_at_front(list,node);
	else {
		Node *curr = list->head;
		while (curr != NULL && (*compare)(node->data,curr->data)) {
			curr = curr->nextPtr;
		}
		if(!curr) //if is the last element of the list
			insert_at_back(list,node);
		else { //insert between two node
			list->size++;
			node->nextPtr = curr;
			node->prevPtr = curr->prevPtr;
			Node **res = list->head == curr ? &(list->head) : &(curr->prevPtr->nextPtr); //if insert at the first element of the list
			*res = node;
			curr->prevPtr = node;
		}
	}
}

void *top_list(const List* list) {
	if(list->head != NULL)
		return list->head->data;
	else
		fprintf(stderr,"The list is empty\n");
	
	return NULL;
}

void *tail_list(const List *list){
	if(list->tail != NULL)
		return list->tail->data;
	else
		fprintf(stderr,"The list is empty\n");
	
	return NULL;
}

void *top_and_delete(List *list){
	if(list->head != NULL){
		list->size--;
		void *ret = malloc(list->type_size);
		memcpy(ret,list->head->data,list->type_size);
		Node *tmp = list->head;
		if(list->head->nextPtr)
			list->head->nextPtr->prevPtr = NULL;
		list->head = list->head->nextPtr;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		return ret;
	}
	else
		fprintf(stderr,"The list is empty\n");
	
	return NULL;
}
void *tail_and_delete(List *list){
	if(list->tail != NULL){
		list->size--;
		void *ret = malloc(list->type_size);
		memcpy(ret,list->tail->data,list->type_size);
		Node *tmp = list->tail;
		if(list->tail->prevPtr)
			list->tail->prevPtr->nextPtr = NULL;
		list->tail = list->tail->prevPtr;
		free(tmp->data);
		tmp->data = NULL;
		free(tmp);
		return ret;
	}
	else
		fprintf(stderr,"The list is empty\n");
	
	return NULL;
}

void search_delete(List *list, void *data, bool (*equal)(const void*, const void*)) {
	Node *curr = list->head;
	while(curr != NULL) {
		Node *next = curr->nextPtr; //save next because curr will be delete 
		if((*equal)(curr->data,data)) {
			Node *tmp = curr;//node to delete
			list->size--;
			if(!curr->prevPtr && !curr->nextPtr) {//control if the list have one element
				free(tmp->data);
				free(tmp);
				list->head = NULL;
				list->tail = NULL;
				return ;
			}
			if(curr->prevPtr  && curr->nextPtr ) {//if the element is between two node
				curr->nextPtr->prevPtr = curr->prevPtr;
				curr->prevPtr->nextPtr = curr->nextPtr;
			}else if(!curr->prevPtr) {//if is the first element
				list->head = curr->nextPtr;
				curr->nextPtr->prevPtr = NULL;
			}else {//if is the last element
				list->tail = curr->prevPtr;
				curr->prevPtr->nextPtr = NULL;
			}
			free(tmp->data);
			free(tmp);
			return;
		}
		curr = next;
	}
	printf("No data is found\n");
}

void print_list(const List *list, void (*your_print)(const void *)) {
	Node *tmp = list->head;
	while(tmp != NULL) {
		(*your_print)(tmp->data);
		tmp = tmp->nextPtr;
	}
	printf("NULL\n");
}

void delete_list(List *list) {
	while (list->head != NULL)
	{
		Node *tmp = (list->head);
		free((list->head)->data);	//first delete memory allocate for pointer to void
		(list->head)->data = NULL;
		list->head = (list->head)->nextPtr;
		free(tmp);				//afeter delete the node
	}
	list->size = 0;
	list->head = NULL;
	list->tail = NULL;
}

List *new_list(size_t type){
	List *l = (List*)malloc(sizeof(List));
	l->type_size = type;
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
	return l;
}

void copy_list(List *dst_list, const List *src_list) {
	delete_list(dst_list);
	const Node * _tmp_head = src_list->head;
	while (_tmp_head)
	{
		insert_at_back(dst_list , new_node((_tmp_head->data),src_list));
		_tmp_head = _tmp_head->nextPtr;
	}
}

bool equal_list(const List *_first, const List* _second, bool (*equal)(const void*, const void*)) {
	if(_first->size == _second->size) {
		const Node *f_tmp = _first->head;
		const Node *s_tmp = _second->head;
		while(f_tmp && s_tmp) {
			if(!(*equal)(f_tmp->data,s_tmp->data)) 
				return false;
			f_tmp = f_tmp->nextPtr;
			s_tmp = s_tmp->nextPtr;
		}
		return true;
	}
	return false;
}

Node *cr_n(void* data) {
	Node *newPtr = (Node *)malloc(sizeof(Node));
	if(newPtr == NULL) {
		fprintf(stderr,"No memory aviable\n");
		exit(EXIT_FAILURE);
	}
	newPtr->data = data;
	newPtr->nextPtr = NULL;
	newPtr->prevPtr = NULL;

	return newPtr;
}

List *create_third_list(List *_f, List *_s, size_t _type, void *(*fun)(void*,void*)) {
	List *dst = new_list(_type);
	Node *f_tmp = _f->tail;
	Node *s_tmp = _s->tail;
	while(f_tmp && s_tmp) {
		insert_at_front(dst,cr_n((*fun)(f_tmp->data,s_tmp->data)));
		f_tmp = f_tmp->prevPtr;
		s_tmp = s_tmp->prevPtr;
	}
	return dst;
}
