#include <stdlib.h>
#include <string.h>
#include "dynamic_string.h"

t_string	*string_create(const char *str)
{
	t_string	*string;

	string = malloc(sizeof(t_string));
	if (!string)
		return (NULL);
	string->length = strlen(str);
	string->data = malloc(string->length + 1);
	if (!string->data)
	{
		free(string);
		return (NULL);
	}
	strcpy(string->data, str);
	return (string);
}

void	string_destroy(t_string *str)
{
	if (str)
	{
		free(str->data);
		free(str);
	}
}

t_string	*string_copy(const t_string *str)
{
	return (string_create(str->data));
}

t_string	*string_concat(const t_string *str1, const t_string *str2) {
	t_string	*result;

	result = malloc(sizeof(t_string));
	if (!result)
		return (NULL);
	result->length = str1->length + str2->length;
	result->data = malloc(result->length + 1);
	if (!result->data)
	{
		free(result);
		return (NULL);
	}
	strcpy(result->data, str1->data);
	strcat(result->data, str2->data);
	return (result);
}

size_t	string_length(const t_string *str)
{
	return (str->length);
}

int	string_compare(const t_string *str1, const t_string *str2)
{
	return (strcmp(str1->data, str2->data));
}

t_string	*string_substring(const t_string *str, size_t start, size_t length)
{
	char		*temp;
	t_string	*result;

	if (start + length > str->length)
		return (NULL);
	temp = malloc(length + 1);
	if (!temp)
		return (NULL);
	strncpy(temp, str->data + start, length);
	temp[length] = '\0';
	result = string_create(temp);
	free(temp);
	return (result);
}
