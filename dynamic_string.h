#ifndef DYNAMIC_STRING_H
# define DYNAMIC_STRING_H

# include <stddef.h>

typedef struct s_string
{
	char*	data;
	size_t	length;
}	t_string;

t_string*	string_create(const char* str);
void		string_destroy(t_string* str);
t_string*	string_copy(const t_string* str);
t_string*	string_concat(const t_string* str1, const t_string* str2);
size_t		string_length(const t_string* str);
int			string_compare(const t_string* str1, const t_string* str2);
t_string*	string_substring(const t_string* str, size_t start, size_t length);

#endif
