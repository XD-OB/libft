/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:15:23 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/18 08:18:12 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			init_node(t_fmt *node)
{
	node->arglist = NULL;
	node->color = NULL;
	node->precis = -1;
	node->width = 0;
	node->convers = '\0';
	node->pos = 0;
	node->argn = 0;
}

static t_fmt	*create_node(void)
{
	t_fmt		*node;

	node = (t_fmt*)malloc(sizeof(t_fmt));
	init_node(node);
	node->next = NULL;
	return (node);
}

static void		advance_free(t_fmt **node, int *p)
{
	if ((*node)->color)
		free((*node)->color);
	if ((*node)->arglist)
		free((*node)->arglist);
	free(*node);
	*p = -1;
}

t_fmt			*parse_format(va_list ap, char *str, int *pflag)
{
	t_fmt		*head;
	t_fmt		*node;
	long		i;

	i = -1;
	head = NULL;
	while (str[++i])
	{
		if (str[i] == '%')
		{
			if (!str[++i])
				return (head);
			node = create_node();
			if (check_fill(ap, &str[i], i - 1, node) != -1)
			{
				head = add_node(head, node);
				while (str[i] && str[i] != node->convers)
					i++;
			}
			else
				advance_free(&node, pflag);
			node = node->next;
		}
	}
	return (head);
}
