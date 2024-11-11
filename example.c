#include "dynamic_array.h"
#include <stdio.h>

int main(void)
{
	t_array	*arr = array_init(2, sizeof(int));

	arr->append(arr, &(int){1});
	arr->append(arr, &(int){2});
	arr->append(arr, &(int){3});
	arr->append(arr, &(int){4});
	/*
	** Be careful when using pointer to pointer
	** the following code will not work
	** the array will store the address of the pointer
	** and not the value of the pointer
	** which will cause potential issues that may crash your program
	** 
	** t_array	*arr = array_init(2, sizeof(char *));
	** char	*str = "Hello";
	** arr->append(arr, &str);
	*/

	for (size_t i = 0; i < arr->size; i++)
		printf("%d\n", *(int *)arr->get(arr, i));
}
