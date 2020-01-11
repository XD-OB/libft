#include "libft.h"

void		ft_lstinsert(t_list **alst, t_list *place, t_list *node)
{
	t_list	*curr;

	if (!*alst)
		*alst = node;
	else
	{
		curr  = *alst;
		while (curr && curr != place)
			curr = curr->next;
		if (!curr)
			return ;
		node->next = curr->next;
		curr->next = node;
	}
}
