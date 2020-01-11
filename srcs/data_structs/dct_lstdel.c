#include "libft.h"

void			dct_lstdel(t_dlist **alst, void (*del)(void*, size_t))
{
	t_dlist		*curr;

	curr = *alst;
	while (curr && curr->next != *alst)
		curr = curr->next;
	curr->next = NULL;
	(*alst)->prev = NULL;
	dt_lstdel(alst, del);
}
