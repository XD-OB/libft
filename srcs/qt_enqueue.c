#include "libft.h"

int			qt_enqueue(t_queue *queue, void *content, size_t size)
{
	t_list	*node;

	if (!(node = ft_lstnew(content, size)))
		return (1);
	if (qt_isempty(*queue))
	{
		queue->front = node;
		queue->rear = queue->front;
	}
	else
	{
		queue->rear->next = node;
		queue->rear = node;
	}
	return (0);
}
