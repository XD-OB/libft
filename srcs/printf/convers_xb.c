/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_xb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 04:08:02 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 17:56:48 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		xx_nres_annex(char **res, char *nbr, int len_nbr, int width)
{
	int			i;

	i = -1;
	while (++i < len_nbr)
		(*res)[i] = nbr[i];
	while (i < width)
		(*res)[i++] = ' ';
}

/*
**	var[2]		0: i	1: j
*/

static char		*xx_nres(t_fmt *fmt, char *nbr, int len_nbr, int base)
{
	int			var[2];
	char		*res;
	char		c;

	c = (fmt->precis == -1 && fmt->zero && !fmt->minus) ? '0' : ' ';
	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (!fmt->minus)
	{
		var[0] = -1;
		while (++(var[0]) < fmt->width - len_nbr)
			res[var[0]] = c;
		if (fmt->dash && c == '0')
		{
			res[1] = (base == 16) ? 'x' : 'b';
			nbr[1] = '0';
		}
		var[1] = -1;
		while (++(var[1]) < len_nbr)
			res[(var[0])++] = nbr[var[1]];
	}
	else
		xx_nres_annex(&res, nbr, len_nbr, fmt->width);
	return (res);
}

/*
**	var[3]		0: is_dash	1: i	2: j
*/

static char		*xx_n(t_fmt *fmt, char *num, int len_num, int base)
{
	int			len_nbr;
	int			var[3];
	char		*res;
	char		*nbr;

	var[0] = (fmt->dash) ? 2 : 0;
	len_nbr = ft_max(len_num, fmt->precis) + var[0];
	nbr = (char*)malloc(sizeof(char) * (len_nbr + 1));
	nbr[len_nbr] = '\0';
	var[1] = len_nbr;
	var[2] = len_num;
	while (--(var[2]) >= 0)
		nbr[--(var[1])] = num[var[2]];
	while (--(var[1]) >= 0)
		nbr[var[1]] = '0';
	if (var[0])
		nbr[1] = (base == 16) ? 'x' : 'b';
	if (fmt->width - len_nbr > 0)
	{
		res = xx_nres(fmt, nbr, len_nbr, base);
		free(nbr);
		return (res);
	}
	return (nbr);
}

void			conv_xx(t_fmt *fmt, t_chr **chr, va_list ap)
{
	unsigned long long int	n;
	char					*num;
	char					*res;

	flag_star(fmt, ap);
	n = (flag_dollar(fmt)) ? cast_xxoub(*(fmt->arglist), fmt)
				: cast_xxoub(ap, fmt);
	if (n == 0)
		res = xx_zero(fmt);
	else
	{
		num = ft_ulltoa_base(n, 16);
		res = xx_n(fmt, num, (int)ft_strlen(num), 16);
		free(num);
	}
	(fmt->convers == 'x') ? res = ft_strlowcase(res) : 0;
	(fmt->convers == 'X') ? res = ft_strupcase(res) : 0;
	(*chr)->str = res;
	(*chr)->len = ft_strlen(res);
}

void			conv_b(t_fmt *fmt, t_chr **chr, va_list ap)
{
	unsigned long long int	n;
	char					*num;
	char					*res;

	flag_star(fmt, ap);
	n = (flag_dollar(fmt)) ? cast_xxoub(*(fmt->arglist), fmt)
				: cast_xxoub(ap, fmt);
	if (n == 0)
		res = xx_zero(fmt);
	else
	{
		num = ft_itoa_base(n, 2);
		res = xx_n(fmt, num, (int)ft_strlen(num), 2);
		free(num);
	}
	(fmt->convers == 'b') ? ft_strlowcase(res) : 0;
	(fmt->convers == 'B') ? ft_strupcase(res) : 0;
	(*chr)->str = res;
	(*chr)->len = ft_strlen(res);
}
