#include "libft.h"

void			ct_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list		*curr;

	curr = *alst;
	while (curr && curr->next != *alst)
		curr = curr->next;
	curr->next = NULL;
	ft_lstdel(alst, del);
}
