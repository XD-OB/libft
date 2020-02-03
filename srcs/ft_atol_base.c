/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishaimou <ilyass.sh@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 21:17:20 by ishaimou          #+#    #+#             */
/*   Updated: 2018/12/17 16:58:51 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_val(char c, char *base)
{
	size_t	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

long		ft_atol_base(char *str, char *base_from)
{
	long	nbr;
	int	n;
	size_t	i;
	size_t	power;
	size_t	base_len;

	nbr = 0;
	power = 1;
	base_len = ft_strlen(base_from);
	i = ft_strlen(str);
	while (i-- > 0)
	{
		n = ft_get_val(str[i], base_from);
		if (n < 0)
			return (0);
		nbr += n * power;
		power *= base_len;
	}
	return (nbr);
}
