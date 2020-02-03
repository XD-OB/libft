/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ztoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:37:16 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/17 07:08:49 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		len_res(size_t nbr, int base)
{
	size_t		len;

	len = 1;
	while (nbr /= base)
		len++;
	return (len);
}

char			*ft_ztoa_base(size_t nbr, int base)
{
	size_t		len;
	char		*res;

	len = len_res(nbr, base);
	if (!(res = ft_strnew(len)))
		return (NULL);
	while (len-- > 0)
	{
		if (nbr % base < 10)
			res[len] = (nbr % base) + '0';
		else
			res[len] = (nbr % base) + 'A' - 10;
		nbr /= base;
	}
	return (res);
}
