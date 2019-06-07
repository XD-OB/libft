#include "libft.h"

void	*sk_top(t_list *top)
{
	void	*item;

	if (!top)
		return (NULL);
	item = (void*)ft_memalloc(top->content_size);
	ft_memcpy(item, top->content, top->content_size);
	return (item);
}
