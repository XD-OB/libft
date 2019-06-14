/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:43:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/12 01:09:10 by obelouch         ###   ########.fr       */
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

void		init_chr(t_chr **chr)
{
	(*chr)->str = NULL;
	(*chr)->len = 0;
	(*chr)->next = NULL;
}

int			fmtlen(t_fmt *fmt)
{
	t_fmt	*curr;
	int		size;

	size = 0;
	curr = fmt;
	while (curr)
	{
		size++;
		curr = curr->next;
	}
	return (size);
}

void		free_chr(t_chr **chr)
{
	t_chr	*curr;
	t_chr	*next;

	curr = *chr;
	while (curr)
	{
		next = curr->next;
		if (curr->str)
			free(curr->str);
		free(curr);
		curr = next;
	}
	*chr = NULL;
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
