/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 01:28:50 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/20 06:19:37 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_verif(size_t a, int sign)
{
	int	nbr;

	if (sign == -1 && (a - 1) > INT_MAX)
		return (0);
	if (sign == 1 && a > INT_MAX)
		return (-1);
	nbr = a * sign;
	return (nbr);
}

int		ft_atoi(const char *str)
{
	size_t	i;
	size_t	a;
	int	sign;

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
		if (ft_isdigit(str[i]))
			a = (a * 10) + (str[i] - 48);
		else
			break ;
		i++;
	}
	return (int_verif(a, sign));
}
