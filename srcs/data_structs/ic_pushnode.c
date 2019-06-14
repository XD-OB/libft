/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ic_pushnode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:51:13 by obelouch          #+#    #+#             */
/*   Updated: 2019/06/14 16:51:15 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ic_pushnode(t_icase **icase, int value)
{
	t_icase		*node;

	if (!(node = (t_icase*)malloc(sizeof(t_icase))))
		return ;
	node->n = value;
	node->next = (*icase);
	(*icase) = node;
}
