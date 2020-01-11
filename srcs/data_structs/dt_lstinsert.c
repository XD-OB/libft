#include "libft.h"

void			dt_lstinsert(t_dlist **alst, t_dlist *place, t_dlist *node)
{
	t_dlist		*curr;

	if (!*alst)
		*alst = node;
	else
	{
		curr  = *alst;
		while (curr && curr != place)
			curr = curr->next;
		if (!curr)
			return ;
		node->prev = curr;
		node->next = curr->next;
		if (curr->next)
			curr->next->prev = node;
		curr->next = node;
	}
}
