#include "libft.h"

void			dt_lstadd_last(t_dlist **alst, t_dlist* new)
{
	t_dlist		*current;

	if (!new)
		return ;
	if (*alst)
	{
		current = *alst;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
	else
		*alst = new;
}
