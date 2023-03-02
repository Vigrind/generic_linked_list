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
	insert_back(l_int, a);
	insert_front(l_int, b);
	lprint(l_int, print_int);

	/* Delete an element from int list*/
	int del_int = rand() % 20;
	printf("Element to delete: %d\n",del_int);
	search_and_delete(l_int, del_int, equal_int);
	lprint(l_int, print_int); /* print the list delete */

	/* create a prova list */
	printf("\nInit and print prova list\n");
	init_prova_list(l_prova);
	lprint(l_prova, print_prova);
	printf("\n");

	/* Create a copy of int list*/
	List *cpy_l_int = new_list(sizeof(int));
	list_copy(cpy_l_int, l_int);
	lprint(cpy_l_int, print_int);
	printf("\n");

	/* Create a copy of prova list*/
	List *cpy_l_prova = new_list(sizeof(prova));
	list_copy(cpy_l_prova, l_prova);
	lprint(cpy_l_prova, print_prova);
	printf("\n");

	/*Create a third list whit the value the sum of cpy_l_int and l_int*/
	List *thrd_list = crt_third_list(sizeof(int), cpy_l_int, l_int, sum_elem);
	lprint(thrd_list, print_int);
	printf("\n");

	/* Top from int list*/
	int *t_int = top(l_int);
	printf("%d\n", *t_int);
	
	/* Top from prova list*/
	prova *t_prova = top(l_prova);
	printf("%c, %f\n", t_prova->a, t_prova->b);

	/* Top and delete*/
	int *td_int = top_delete(l_int);
	printf("%d\n", *td_int);
	lprint(l_int, print_int);
	printf("\n");

	/* Tail and delete*/
	prova *td_prova = tail_delete(l_prova);
	printf("%c, %f\n", td_prova->a, td_prova->b);
	lprint(l_prova, print_prova);
	printf("\n");

	/* Equal list */
	if (lequal(cpy_l_int, l_int, equal_int) == true)
		printf("the int list are equal\n");
	else
		printf("not equal\n");

	/* delete all the list and free their pointer */
	ldelete(cpy_l_int);
	ldelete(l_int);
	ldelete(l_prova);
	ldelete(cpy_l_prova);
	ldelete(thrd_list);
	free(cpy_l_int);
	free(l_int);
	free(l_prova);
	free(cpy_l_prova);
	free(thrd_list);
	
	/* free memory returned by top or tail and delete*/
	free(td_int);
	free(td_prova);
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
		insert_order(_l, a, comp_int);
		//_l->functions->insert_in_order(_l, _l->functions->new_node(&a, _l), comp_int);
	}
}

void init_prova_list(List *_l){
	for (size_t i = 0; i < 20; i++)
	{
		prova p = {
			.a = 97 + (rand() % 25),
			.b = (rand() % 20) / 5
		};
		insert_front(_l, p);
	}
}