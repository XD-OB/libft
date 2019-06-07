#include "libft.h"

/*
**	For simple Pop: item=NULL
**	Else: item is affected with the content of deleted node
*/

void	sk_pop(t_list **top, void *item)
{
	t_list	*tmp;

	if (sk_isempty(*top))
	{
		(item) ? item = NULL : 0;
		return ;
	}
	tmp = *top;
	*top = (*top)->next;
	(item) ? item = sk_top(tmp) : 0;
	if (tmp->content)
		free(tmp->content);
	free(tmp);
}
