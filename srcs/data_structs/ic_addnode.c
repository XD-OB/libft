/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ic_addnode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:51:06 by obelouch          #+#    #+#             */
/*   Updated: 2019/06/14 16:51:09 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ic_addnode(t_icase **icase, int value)
{
	t_icase		*node;

	node = (*icase)->next;
	if (!(node = (t_icase*)malloc(sizeof(t_icase))))
		return ;
	node->n = value;
	node->next = NULL;
}
