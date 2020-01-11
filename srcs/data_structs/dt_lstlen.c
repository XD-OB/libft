#include "libft.h"

int			dt_lstlen(t_dlist *lst)
{
	int		len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}
