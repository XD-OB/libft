#include "libft.h"

void	dt_lstiter(t_dlist *lst, void (*f)(t_dlist *elem))
{
	if (f)
	{
		while (lst != NULL)
		{
			f(lst);
			lst = lst->next;
		}
	}
}
