/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 05:49:26 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 07:11:41 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		len_res(unsigned long long nbr)
{
	size_t		len;

	len = 1;
	while (nbr /= 10)
		len++;
	return (len);
}

char			*ft_ulltoa(unsigned long long nbr)
{
	char		*res;
	size_t		len;

	len = len_res(nbr);
	if (!(res = ft_strnew(len)))
		return (NULL);
	while (len-- > 0)
	{
		res[len] = (nbr % 10) + 48;
		nbr /= 10;
	}
	return (res);
}
