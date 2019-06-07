#include "libft.h"

int		qt_isempty(t_queue queue)
{
		if (!queue.front)
			if (!queue.rear)
				return (1);
		return (0);
}
