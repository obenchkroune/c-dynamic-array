#include "dynamic_array.h"
#include <stdlib.h>
#include <string.h>


static void array_resize(t_array* arr)
{
	size_t new_capacity = arr->capacity * 2;
	void*  new_array    = malloc(new_capacity * arr->element_size);

	memcpy(new_array, arr->array, arr->size * arr->element_size);

	free(arr->array);
	arr->array    = new_array;
	arr->capacity = new_capacity;
}

static void array_append(t_array* arr, void* element)
{
	if (arr->size >= arr->capacity)
	{
		array_resize(arr);
	}
	memcpy((char*)arr->array + (arr->size * arr->element_size), element, arr->element_size);
	arr->size++;
}

static void array_remove(t_array* arr, size_t index)
{
	if (index >= arr->size)
		return;

	char*  src           = (char*)arr->array + ((index + 1) * arr->element_size);
	char*  dst           = (char*)arr->array + (index * arr->element_size);
	size_t bytes_to_move = (arr->size - index - 1) * arr->element_size;

	memmove(dst, src, bytes_to_move);
	arr->size--;
}

static void* array_get(t_array* arr, size_t index)
{
	if (index >= arr->size)
		return NULL;
	return (char*)arr->array + (index * arr->element_size);
}

static void free_array(t_array* arr)
{
	free(arr->array);
	free(arr);
}

static void reserve(t_array* arr, size_t new_capacity)
{
	void	*new_array;
	if (new_capacity <= arr->capacity)
		return;

	new_array = malloc(new_capacity * arr->element_size);
	if (!new_array)
		return;
	memcpy(new_array, arr->array, arr->size * arr->element_size);
	free(arr->array);
	arr->array = new_array;
	arr->capacity = new_capacity;
}

t_array *array_init(size_t initial_capacity, size_t element_size)
{
	t_array	*arr;

	arr = malloc(sizeof(t_array));
	if (!arr)
		return (NULL);
	arr->array= malloc(initial_capacity * element_size);
	if (!arr->array)
		return (free(arr), NULL);
	arr->size = 0;
	arr->capacity = initial_capacity;
	arr->element_size = element_size;
	arr->reserve = reserve;
	arr->append = array_append;
	arr->get = array_get;
	arr->remove = array_remove;
	arr->free = free_array;
	return arr;
}
