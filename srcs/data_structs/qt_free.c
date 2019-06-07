#include "libft.h"

void			qt_free(t_queue *queue)
{
	t_list		*curr;
	t_list		*tmp;

	curr = queue->front;
	while (curr)
	{
		free(curr->content);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}
