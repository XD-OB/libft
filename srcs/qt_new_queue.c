#include "libft.h"

t_queue		qt_new_queue(void)
{
	t_queue	queue;

	queue.front = NULL;
	queue.rear = NULL;
	return (queue);
}
