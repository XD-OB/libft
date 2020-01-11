#include "libft.h"

void    ct_lstadd_last(t_list **alst, t_list* new)
{
	t_list  *current;

	if (!new)
		return ;
	if (*alst)
	{
		current = *alst;
		while (current->next != *alst)
			current = current->next;
		current->next = new;
		new->next = *alst;
	}
	else
		*alst = new;
}
