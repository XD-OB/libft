#include "libft.h"

char			*ic_joinstr(t_icase **icase, int size)
{
	char		*res;
	t_icase		*tmp;
	int			i;

	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	res[size] = '\0';
	i = size;
	while (*icase && --i >= 0)
	{
		tmp = *icase;
		res[i] = (*icase)->n + 48;
		*icase = (*icase)->next;
		free(tmp);
	}
	return (res);
}
