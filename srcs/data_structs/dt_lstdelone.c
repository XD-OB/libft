#include "libft.h"

void	dt_lstdelone(t_dlist **alst, void (*del)(void*, size_t))
{
	if (alst)
	{
		if (*alst && del)
		{
			del((*alst)->content, (*alst)->content_size);
			(*alst)->prev = NULL;
			(*alst)->next = NULL;
			free(*alst);
			*alst = NULL;
		}
	}
}
