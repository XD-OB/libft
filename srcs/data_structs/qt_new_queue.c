/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qt_new_queue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 16:52:51 by obelouch          #+#    #+#             */
/*   Updated: 2019/06/14 16:52:52 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_queue		qt_new_queue(void)
{
	t_queue	queue;

	queue.front = NULL;
	queue.rear = NULL;
	return (queue);
}
