#include "libft.h"

void	dt_lstadd(t_dlist **alst, t_dlist *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	(*alst)->prev = new;
	*alst = new;
}
