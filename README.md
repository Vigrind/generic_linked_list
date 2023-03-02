# Generic Double Linked List
## How to use
Firs of all, you must create a pointer to type List, for example List *l = new_list(sizeof(int));\
After you can use the macro described below to create and manage your list.


List of all function you can use for manage a List:
|Name|Example of use|Brief Description|
|----|--------------|-----------------|
|<span style="color: yellow">insert_front</span>|insert_front(list, elem)|inserts an element at the top of the list
|<span style="color: yellow">insert_back</span>|insert_back(list, elem)|inserts an element at the tail of the list
|<span style="color: yellow">insert_order</span>|insert_order(list, elem, compare_function)|inserts an element in order (with duplicate)
|<span style="color: yellow">n_node</span>|n_node(elem, list)|create a new node 
|<span style="color: yellow">top</span>|top(list)|return a pointer to the top element of the list
|<span style="color: yellow">top_delete</span>|top_delete(list)|return a pointer to the top element of the list, **remember to free the memory returned by top_delete**
|<span style="color: yellow">tail</span>|tail(list)|return a pointer to the tail element of the list
|<span style="color: yellow">tail_delete</span>|tail_delete(list)|return a pointer to the tail element of the list. **remember to free the memory returned by tail_delete**
|<span style="color: yellow">ldelete</span>|ldelete(list)|delete all element of the list
|<span style="color: yellow">lprint</span>|lprint(list, your_print_function)|print the list
|<span style="color: yellow">search_and_delete</span>|search_and_delete(list, elem, your_equal_function)|delete a specific item, and all its occurrences
|<span style="color: yellow">list_copy</span>|list_copy(dest_list, source_list)|create a copy of the source_list in dest_list
|<span style="color: yellow">lequal</span>|lequal(first_list, second_list, your_equal_function)|return true(1) if the list are equal, 0 otherwise
|<span style="color: yellow">crt_third_list</span>|List *third_list = crt_third_list(sizeof(int), first_list, second_list, your_create_function)|Create a third list by scrolling through both **_first_list_** and **_second_list_**, pass the element of the **_first_** and **_second_** to the `your_create_function`. The element in the third list will be equal to the result of `your_create_function`

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