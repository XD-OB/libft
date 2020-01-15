#include "libft.h"

char		**tabstr_new(size_t len)
{
	char	**tab;

	if (!(tab = (char**)malloc(sizeof(char*) * (len + 1))))
		return NULL;
	tab[len] = NULL;
	return (tab);
}
