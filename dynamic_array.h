#ifndef DYNAMIC_ARRAY_H
# define DYNAMIC_ARRAY_H

# include <stdio.h>

typedef struct s_array
{
	void	*array;
	size_t	size;
	size_t	capacity;
	size_t	element_size;
	void	(*reserve)(struct s_array* arr, size_t new_capacity);
	void	(*append)(struct s_array* arr, void* element);
	void	*(*get)(struct s_array* arr, size_t index);
	void	(*remove)(struct s_array* arr, size_t index);
	void	(*destroy)(struct s_array* arr);
}	t_array;

t_array	*array_init(size_t initial_capacity, size_t element_size);


#endif // DYNAMIC_ARRAY_H
