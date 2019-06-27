/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:43:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/06/29 04:06:04 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_fmt		*add_node(t_fmt *head, t_fmt *node)
{
	t_fmt	*current;

	current = head;
	if (!head)
		return (node);
	while (current->next)
		current = current->next;
	current->next = node;
	return (head);
}

int			fmtlen(t_fmt *fmt)
{
	int		size;

	size = 0;
	while (fmt)
	{
		size++;
		fmt = fmt->next;
	}
	return (size);
}

void		free_fmt(t_fmt **fmt)
{
	t_fmt	*curr;
	t_fmt	*next;

	curr = *fmt;
	while (curr)
	{
		next = curr->next;
		if (curr->color)
			free(curr->color);
		if (curr->arglist)
			free(curr->arglist);
		free(curr);
		curr = next;
	}
	*fmt = NULL;
}
