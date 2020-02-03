/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 05:49:26 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 07:12:32 by ishaimou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_lltoa(long long nbr)
{
	unsigned long long	tmp;
	size_t			len;
	size_t			sign;
	char			*res;

	sign = (nbr < 0) ? 1 : 0;
	len = sign + 1;
	tmp = ABS(nbr);
	while (tmp /= 10)
		len++;
	if (!(res = ft_strnew(len)))
		return (res);
	if (sign)
		res[0] = '-';
	tmp = ABS(nbr);
	while (len-- > sign)
	{
		res[len] = (tmp % 10) + 48;
		tmp /= 10;
	}
	return (res);
}
