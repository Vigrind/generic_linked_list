#include "gstruct.h"
#include <time.h>

//create my print
void print_int(const void *_data);
void print_prova(const void *_data);
bool equal_int(const void *_first, const void *_second);
bool comp_int(const void *_first, const void *_second);
void *sum_elem(void *a, void *b);
void init_int_list(List *_l);
void init_prova_list(List *l);

typedef struct prova {
	char a;
	float b;
}prova;

int main(void) {
	srand(time(NULL));
	__attribute_maybe_unused__ prova prov = {
		'A',
		34.54,
	};
	List *l_int = new_list(sizeof(int));
	List *l_prova = new_list(sizeof(prova));

	/* create an int list */
	printf("\nInit and print the integer list\n");
	init_int_list(l_int);
	int a = 1000;
	int b = -1;
	insert_at_back(l_int,new_node(&a,l_int));
	insert_at_front(l_int,new_node(&b,l_int));
	print_list(l_int,&print_int);

	/* Delete an element from int list*/
	int del_int = rand() % 20;
	printf("Element to delete: %d\n",del_int);
	search_delete(l_int,&del_int,&equal_int);
	print_list(l_int,&print_int); /* print the list delete */

	/* create a prova list */
	printf("\nInit and print prova list\n");
	init_prova_list(l_prova);
	print_list(l_prova,&print_prova);
	printf("\n");

	/* delete all the list and free their pointer */
	delete_list(l_int);
	delete_list(l_prova);
	free(l_int);
	free(l_prova);
}

void print_int(const void *_data) {
	printf("%d-->",*(int *)_data);
}

void print_prova(const void *_data) {
	prova tmp = *(prova *)_data;
	printf("a=%c ",tmp.a);
	printf("b=%f-->",tmp.b);
}

bool equal_int(const void *_first, const void *_second) {
	return *(int*)_first == *(int*)_second;
}
bool comp_int(const void *_first, const void *_second) {
	return *(int *)_first < *(int *)_second;
}

void *sum_elem(void *a, void *b){
	int *res = (int*)malloc(sizeof(int));
	*res = *(int*)a + *(int*)b;
	return (void*)res;
}

void init_int_list(List *_l){
	for (size_t i = 0; i < 20; i++)
	{
		int a = rand() % 20;
		insert_in_order(_l,new_node(&a,_l),comp_int);
	}
}

void init_prova_list(List *_l){
	for (size_t i = 0; i < 20; i++)
	{
		prova p = {
			.a = 97 + (rand() % 25),
			.b = (rand() % 20) / 5
		};
		insert_at_front(_l,new_node(&p,_l));
	}
}