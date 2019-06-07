#include "libft.h"

int			qt_front(t_queue queue, void *content)
{
	if (qt_isempty(queue))
		return (1);
	ft_memcpy(content, queue.front->content,
			queue.front->content_size);
	return (0);
}
