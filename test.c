#include "gstruct.h"

//create my print
void printInt(const void *_data);
void printProva(void *_data);

typedef struct prova {
	char a;
	float b;
	struct prova *nextPtr;
}prova;

int main(void) {
	List *l = newList();
	for (size_t i = 0; i < 20; i++)
	{
		//Instead of
		// l->fun->insertAtFront(&(l->head),&l->tail,l->fun->newNode(&i,sizeof(i)),&l->size);
		//We can use macros, like below
		_insertAtFront(l,_newNode(l,i));
	}

	// l->fun->print(l->head,printInt); 
	_print(l,printInt);
	
	//size_t _test_top = *(size_t *)l->fun->top(l->head)
	size_t _test_top = *(size_t *)_top(l)
	printf("\ntop of the list: %zd\n",_test_top);
	
	int search = 13;
	_searchNDelete(l,search);
	_print(l,printInt);

	//l->fun->delete(&l->head,&l->tail);
	for (size_t i = 0; i < 20; i++)
	{
		_searchNDelete(l,i);
	}
	_print(l,printInt);
	_delete(l);
	
	free(l);
}

void printInt(const void *_data) {
	printf("%d-->",*(int *)_data);
}

void printProva(void *_data) {
	prova tmp = *(prova *)_data;
	printf("a=%c ",tmp.a);
	printf("b=%f-->",tmp.b);
}