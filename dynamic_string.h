#ifndef DYNAMIC_STRING_H
# define DYNAMIC_STRING_H

# include <stddef.h>

typedef struct s_string
{
	char				*data;
	size_t				length;
	void				(*destroy)(struct s_string* str);
	struct s_string*	(*copy)(const struct s_string* str);
	struct s_string*	(*concat)(const struct s_string* str1, const struct s_string* str2);
	int					(*compare)(const struct s_string* str1, const struct s_string* str2);
	struct s_string*	(*substring)(const struct s_string* str, size_t start, size_t length);
}	t_string;

t_string*	string_init(const char* str);

#endif
