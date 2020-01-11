#include "libft.h"

void	dct_lstremove(t_dlist **alst, t_dlist *place, void (*del)(void*, size_t))
{
	t_dlist		*curr;
	t_dlist		*tmp;

	if (!alst || !*alst || !del)
		return ;
	curr = *alst;
	while (curr != place)
		curr = curr->next;
	del(curr->content, curr->content_size);
	if (curr->prev == curr->next)
	{
		free(curr);
		curr->prev = NULL;
		curr->next = NULL;
		curr = NULL;
	}
	else
	{
		tmp = curr;
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		curr = curr->prev;
		free(tmp);
		tmp = NULL;
	}
}
