#include "libft.h"

void	ct_lstremove(t_list **alst, t_list *place, void (*del)(void*, size_t))
{
	t_list		*next;
	t_list		*prev;

	if (!alst || !*alst || !del)
		return ;
	prev = *alst;
	if (place != *alst)
	{
		while (prev && prev->next != place)
			prev = prev->next;
		if (!prev)
			return ;
	}
	next = place->next;
	del(place->content, place->content_size);
	free(place);
	prev->next = next;
}
