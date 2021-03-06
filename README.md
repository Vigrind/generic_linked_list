# Generic Double Linked List
## How to use
Firs of all, you must create a pointer to type List, for example List *l = new_list(sizeof(int));\
After you can use the functions described below to create and manage your list.


List of all function you can use for manage a List:
|Name|Example of use|Brief Description|
|----|--------------|-----------------|
|<font color="yellow">list_insert_at_front</font>|list_insert_at_front(list,list_new_node(&elem,list)|inserts an element at the top of the list
|<font color="yellow">list_insert_at_back</font>|list_insert_at_back(list,list_new_node(&elem,list)|inserts an element at the tail of the list
|<font color="yellow">list_insert_in_order</font>|list_insert_in_order(list, list_new_node(&elem,list), your_compare_function)|inserts an element in order (with duplicate)
|<font color="yellow">list_new_node</font>|list_new_node(&elem,list)|create a new node 
|<font color="yellow">list_top</font>|list_list_top(list)|return the top element of the list
|<font color="yellow">list_delete</font>|list_delete(list)|delete all element of the list
|<font color="yellow">list_print</font>|list_print(list, your_print_function)|print the list
|<font color="yellow">list_search_delete</font>|list_search_delete(list, elem, your_equal_function)|delete a specific item, and all its occurrences
|<font color="yellow">list_copy_list</font>|list_copy_list(dest_list,source_list)|create a copy of the source_list
|<font color="yellow">list_equal</font>|list_equal(first_list,second_list,your_equa_function)|return true(1) if the list are equal, 0 otherwise
|<font color="yellow">list_create_third_list</font>|List *third_list = list_create_third_list(first_list,second_list,sizeof(int),your_create_function)|Create a third list by scrolling through both **_first_list_** and **_second_list_**, pass the element of the **_first_** and **_second_** to the `your_create_function`. The element in the third list will be equal to the result of `your_create_function`

**Function that you need to define:**
 * **compare** function, to use in insert_in_order
 * **equal** function, to use in search_delete
 * **print** function, to use in print_list
 * **create** function, to use in create_what_you_want

_Code Example:_
~~~C
bool comp_int(const void *_first, const void *_second) {
	return *(int *)_first < *(int *)_second;
}

bool equal_int(const void *_first, const void *_second) {
	return *(int*)_first == *(int*)_second;
}

void print_int(const void *_data) {
	printf("%d-->",*(int *)_data);
}

void *create_sum_elem(void *a, void *b){
	int *res = (int*)malloc(sizeof(int));
	*res = *(int*)a + *(int*)b;
	return (void*)res;
}

~~~
As in the example **compare** and **equal** function need to be `bool f_name (const void*,const void*)`

The **compare** function control if first element is < or > of second.\
If you set first < the second, the list is in decrescent order, ascending otherwise

The **equal** function simply see if the two argument is equal.

Use the **print** function to print your element

The **create** funciton need to be `void *create_name(const void*, const void*)`.\
The result of create must be a void pointer , remember to allocate memory for the return pointer.\
Don't warry for memory leak, delete_list automatically free the memory