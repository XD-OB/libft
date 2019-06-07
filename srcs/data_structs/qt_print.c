#include "libft.h"

/*
**	type: 		0:number	1:string
**	sep:		0:\n		1:<-
*/

void			qt_print(t_queue queue, int type, int sep)
{
	t_list		*curr;

	if (qt_isempty(queue))
	{
		(sep) ? ft_putstr("Empty Queue!\n") : 0;
		return ;
	}
	curr = queue.front;
	while (curr)
	{
		if (type)
			ft_putstr((char*)curr->content);
		else
			ft_putnbr(*((int*)curr->content));
		ft_putstr((sep) ? " <- " : "\n");
		curr = curr->next;
	}
	(sep) ? ft_putstr("NULL") : 0;
	ft_putchar('\n');
}
