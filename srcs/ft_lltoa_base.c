/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <obelouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 11:37:16 by ishaimou          #+#    #+#             */
/*   Updated: 2019/04/17 07:05:08 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_lltoa_base(long long nbr, int base)
{
	unsigned long long	tmp;
	size_t			len;
	size_t			sign;
	char			*res;

	sign = (nbr < 0) ? 1 : 0;
	len = sign + 1;
	tmp = ABS(nbr);
	while (tmp /= base)
		len++;
	if (!(res = ft_strnew(len)))
		return (NULL);
	tmp = ABS(nbr);
	if (sign)
		res[0] = '-';
	while (len-- > sign)
	{
		if (tmp % base < 10)
			res[len] = (tmp % base) + '0';
		else
			res[len] = (tmp % base) + 'A' - 10;
		tmp /= base;
	}
	return (res);
}
