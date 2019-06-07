#include "libft.h"

int			qt_dequeue(t_queue *queue)
{
	t_list	*tmp;

	if (qt_isempty(*queue))
		return (1);
	tmp = queue->front;
	if (queue->front == queue->rear)
	{
		queue->front = NULL;
		queue->rear = NULL;
	}
	else
		queue->front = queue->front->next;
	free(tmp->content);
	free(tmp);
	return (0);
}
