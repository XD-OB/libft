#include "libft.h"

void	dct_lstremove(t_dlist **alst, t_dlist *place, void (*del)(void*, size_t))
{
	t_dlist		*tmp;

	if (!alst || !*alst || !del || !place)
		return ;
	if (place == *alst && place == place->next)
	{
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = NULL;
	}
	else
	{
		tmp = *alst;
		while (*alst != place)
			*alst = (*alst)->next;
		(*alst)->prev->next = (*alst)->next;
		(*alst)->next->prev = (*alst)->prev;
		del((*alst)->content, (*alst)->content_size);
		if (*alst == tmp)
			
			tmp = tmp->next;
		free(*alst);
		*alst = NULL;
		*alst = tmp;
	}	
}
