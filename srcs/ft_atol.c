/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 06:15:24 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/20 06:16:20 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		long_verif(size_t a, int sign)
{
	long		nbr;

	if (sign == -1 && (a - 1) > LONG_MAX)
		return (0);
	if (sign == 1 && a > LONG_MAX)
		return (-1);
	nbr = a * sign;
	return (nbr);
}

long			ft_atol(const char *str)
{
	size_t	 	a;
	int		i;
	int		sign;

	i = 0;
	a = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] > 47 && str[i] < 58)
			a = (a * 10) + (str[i] - 48);
		else
			break ;
		i++;
	}
	return (long_verif(a, sign));
}
