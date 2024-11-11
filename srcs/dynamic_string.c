#include <stdlib.h>
#include <string.h>
#include "dynamic_string.h"


static void	string_destroy(t_string *str)
{
	if (str)
	{
		free(str->data);
		free(str);
	}
}

static t_string	*string_copy(const t_string *str)
{
	return (string_init(str->data));
}

static int	string_compare(const t_string *str1, const t_string *str2)
{
	return (strcmp(str1->data, str2->data));
}

static t_string	*string_substring(const t_string *str, size_t start, size_t length)
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
	result = string_init(temp);
	free(temp);
	return (result);
}

static t_string	*string_concat(const t_string *str1, const t_string *str2) {
	t_string	*result;

	result = malloc(sizeof(t_string));
	if (!result)
		return (NULL);
	result->length = str1->length + str2->length;
	result->data = malloc(result->length + 1);
	if (!result->data)
		return (free(result), NULL);
	memset(result->data, 0, result->length + 1);
	strlcpy(result->data, str1->data, result->length + 1);
	strlcat(result->data, str2->data, result->length + 1);
	result->compare = string_compare;
    result->concat = string_concat;
    result->copy = string_copy;
    result->destroy = string_destroy;
    result->substring = string_substring;
	return (result);
}

t_string	*string_init(const char *str)
{
	t_string	*string;

	string = malloc(sizeof(t_string));
	if (!string)
		return (NULL);
	string->length = strlen(str);
	string->data = malloc(string->length + 1);
	if (!string->data)
		return (free(string), NULL);
	memset(string->data, 0, string->length + 1);
	strcpy(string->data, str);
	string->compare = string_compare;
	string->concat = string_concat;
	string->copy = string_copy;
	string->destroy = string_destroy;
	string->substring = string_substring;
	return (string);
}
