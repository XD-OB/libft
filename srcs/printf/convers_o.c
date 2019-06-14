/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_xxoub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:35:22 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 17:48:51 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*o_zerores(t_fmt *fmt, char *nbr, int len_nbr, char c)
{
	char		*res;
	int			i;
	int			j;

	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (!fmt->minus)
	{
		i = fmt->width;
		j = len_nbr;
		while (--j >= 0)
			res[--i] = nbr[j];
		while (--i >= 0)
			res[i] = c;
	}
	else
	{
		i = 0;
		j = 0;
		while (j < len_nbr)
			res[i++] = nbr[j++];
		while (i < fmt->width)
			res[i++] = c;
	}
	return (res);
}

static char		*o_zero(t_fmt *fmt)
{
	char		*res;
	int			len_nbr;
	char		*nbr;
	char		c;

	len_nbr = fmt->precis;
	if (fmt->precis == -1 || (!fmt->precis && fmt->dash))
		len_nbr = 1;
	nbr = ft_strcnew(len_nbr, '0');
	if (fmt->width > len_nbr)
	{
		c = (fmt->precis == -1 && fmt->zero)
				&& (!fmt->minus) ? '0' : ' ';
		res = o_zerores(fmt, nbr, len_nbr, c);
		free(nbr);
		return (res);
	}
	return (nbr);
}

void			conv_o(t_fmt *fmt, t_chr **chr, va_list ap)
{
	unsigned long long int	n;
	char					*num;
	char					*res;

	flag_star(fmt, ap);
	n = (flag_dollar(fmt)) ? cast_xxoub(*(fmt->arglist), fmt)
							: cast_xxoub(ap, fmt);
	if (n == 0)
		res = o_zero(fmt);
	else
	{
		num = ft_ulltoa_base(n, 8);
		res = o_n(fmt, num, (int)ft_strlen(num));
		free(num);
	}
	(*chr)->str = res;
	(*chr)->len = ft_strlen(res);
}
