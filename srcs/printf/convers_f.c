/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 00:38:44 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 16:59:15 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*custom_fannex2(t_fmt *fmt, char *str, long *len, int sign)
{
	long	i;
	long	j;
	char	*res;

	j = *len;
	i = fmt->width;
	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	while (j > 0)
		res[--i] = str[--j];
	while (i > 0)
		res[--i] = '0';
	if (sign)
		res[0] = '-';
	else if (fmt->plus)
		res[0] = '+';
	else if (fmt->space)
		res[0] = ' ';
	return (res);
}

static char	*custom_fannex(t_fmt *fmt, char *str, long *len, int sign)
{
	long	i;
	long	j;
	char	*res;

	if (fmt->zero)
		res = custom_fannex2(fmt, str, len, sign);
	else
	{
		j = *len;
		i = fmt->width;
		res = (char*)malloc(sizeof(char) * (fmt->width + 1));
		res[fmt->width] = '\0';
		while (j > 0)
			res[--i] = str[--j];
		if (sign)
			res[--i] = '-';
		else if (fmt->plus)
			res[--i] = '+';
		while (i > 0)
			res[--i] = ' ';
	}
	*len = fmt->width;
	return (res);
}

/*
**	v[2]:		0: i		1: j
*/

void		customize_f(t_fmt *fmt, char **str, long *len, int sign)
{
	char	*res;
	long	v[2];

	if (fmt->minus)
	{
		v[0] = 0;
		v[1] = 0;
		res = (char*)malloc(sizeof(char) * (fmt->width + 1));
		res[fmt->width] = '\0';
		if (sign)
			res[v[0]++] = '-';
		else if (fmt->plus)
			res[v[0]++] = '+';
		else if (fmt->space)
			res[v[0]++] = ' ';
		while (v[1] < *len)
			res[v[0]++] = (*str)[v[1]++];
		*len = fmt->width;
		while (v[0] < *len)
			res[v[0]++] = ' ';
	}
	else
		res = custom_fannex(fmt, *str, len, sign);
	free(*str);
	*str = res;
}

/*
**	v[3]:		0: len		1: carry	2: base
*/

void		conv_lfh(t_fmt *fmt, t_chr **chr, t_double db, int is_g)
{
	long	v[3];
	char	*fract;
	char	*entier;

	v[1] = 0;
	v[2] = (fmt->convers == 'H') ? 16 : 10;
	if (pre_d_calc(db, chr, fmt, is_g))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, fmt);
	(v[2] == 16) ? flag_dash(&entier, 16) : 0;
	flag_apostrophe(&entier, fmt);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, fmt);
	if (is_g)
		fmt->precis = ft_max((fmt->precis - ft_strlen(entier)), 1);
	fprecis(&fract, fmt->precis, &v[1], v[2]);
	(v[1] == 1) ? sumstr(&entier, "1", v[2]) : 0;
	(*chr)->str = ft_pointjoin(fmt, entier, fract, &v[0]);
	(fmt->width > v[0]) ?
		customize_f(fmt, &((*chr)->str), &v[0], db.zone.sign) :
		add_sign_f(fmt, &((*chr)->str), &v[0], db.zone.sign);
	free(entier);
	free(fract);
	(*chr)->len = v[0];
}
