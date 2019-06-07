#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

typedef	struct	s_node
{
	void		*item;
	size_t		item_size;
	struct s_node	*next;
}				t_node;

typedef struct 	s_queue
{
	t_node		*front;
	t_node		*rear;
}				t_queue;

t_queue		qt_new_queue(void)
{
	t_queue	queue;

	queue.front = NULL;
	queue.rear = NULL;
	return (queue);
}

int			qt_isempty(t_queue queue)
{
		if (!queue.front)
			if (!queue.rear)
				return (1);
		return (0);
}

t_node		*create_node(void *item, int size)
{
	t_node	*node;

	if (!(node = (t_node*)malloc(sizeof(t_node))))
		return (NULL);
	node->next = NULL;
	node->item_size = size;
	if (!(node->item = (void*)ft_memalloc(size)))
	{
		free(node);
		return (NULL);
	}
	ft_memcpy(node->item, item, size);
	return (node);
}

int			qt_enqueue(t_queue *queue, void *item, size_t size)
{
	t_node	*node;

	if (!(node = create_node(item, size)))
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

int			qt_dequeue(t_queue *queue)
{
	t_node	*tmp;

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
	free(tmp);
	return (0);
}

int			qt_front_item(t_queue queue, void *item)
{
	if (qt_isempty(queue))
		return (1);
	ft_memcpy(item, queue.front->item,
			queue.front->item_size);
	return (0);
}

void			qt_free(t_queue *queue)
{
	t_node		*curr;
	t_node		*tmp;

	curr = queue->front;
	while (curr)
	{
		free(curr->item);
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}
}

/*
**	type: 		0:number	1:string
**	sep:		0:\n		1:<-
*/

void			qt_print(t_queue queue, int type, int sep)
{
	t_node		*curr;

	if (qt_isempty(queue))
	{
		(sep) ? ft_putstr("Empty Queue!\n") : 0;
		return ;
	}
	curr = queue.front;
	while (curr)
	{
		if (type)
			ft_putstr((char*)curr->item);
		else
			ft_putnbr(*((int*)curr->item));
		ft_putstr((sep) ? " <- " : "\n");
		curr = curr->next;
	}
	(sep) ? ft_putstr("NULL") : 0;
	ft_putchar('\n');
}

int	main(int ac, char **av)
{
	t_queue	q;
	int	i;
	int	val;

	if (ac > 1)
	{
		i = 0;
		q = qt_new_queue();
		while (++i < ac)
		{
			val = ft_atoi(av[i]);
			qt_enqueue(&q, &val, (size_t)sizeof(int));
		}
		qt_print(q, 0, 1);
		qt_front_item(q, &val);
		ft_printf("front: %d\n", val);
		val = 15;
		qt_enqueue(&q, &val, (size_t)sizeof(int));
		qt_print(q, 0, 1);
		qt_front_item(q, &val);
		ft_printf("front: %d\n", val);
		qt_dequeue(&q);
		qt_print(q, 0, 1);
		qt_front_item(q, &val);
		ft_printf("front: %d\n", val);
		qt_dequeue(&q);
		qt_print(q, 0, 1);
		qt_front_item(q, &val);
		ft_printf("front: %d\n", val);
		val = 19;
		qt_enqueue(&q, &val, (size_t)sizeof(int));
		qt_print(q, 0, 1);
		qt_front_item(q, &val);
		ft_printf("front: %d\n", val);
		qt_dequeue(&q);
		qt_print(q, 0, 1);
		qt_front_item(q, &val);
		ft_printf("front: %d\n", val);
		qt_free(&q);
	}
	return (0);
}
