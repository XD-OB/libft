#include "libft.h"

void	sk_push(t_list **top, void *content, size_t size)
{
	t_list	*node;

	node = ft_lstnew(content, size);
	node->next = *top;
	*top = node;
}
