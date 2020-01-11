#include "libft.h"

void			dct_lstadd_last(t_dlist **alst, t_dlist* new)
{
	t_dlist		*current;

	if (!new)
		return ;
	if (*alst)
	{
		current = *alst;
		while (current->next != *alst)
			current = current->next;
		current->next = new;
		new->next = *alst;
		new->prev = current;
		(*alst)->prev = new;
	}
	else
		*alst = new;
}
