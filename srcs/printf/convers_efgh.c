/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_efgh.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:57:10 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 16:22:09 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		gclean(t_fmt *fmt, t_chr **chr)
{
	char		*clean;
	int			size;
	int			i;

	if (!fmt->dash)
	{
		size = (*chr)->len - 1;
		while (size >= 0 && ((*chr)->str)[size] == '0')
			size--;
		if (((*chr)->str)[size] == '.')
			size--;
		if (size != (int)((*chr)->len))
		{
			clean = (char*)malloc(sizeof(char) * size + 2);
			clean[size + 1] = '\0';
			i = -1;
			while (++i <= size)
				clean[i] = ((*chr)->str)[i];
			free((*chr)->str);
			(*chr)->str = clean;
			(*chr)->len = size + 1;
		}
	}
}

static void		efgh_annex(t_chr **chr, t_fmt *fmt)
{
	size_t		a;

	a = (fmt->plus || fmt->space) ? 2 : 1;
	if (ft_strlen((*chr)->str) > 1 + a)
		gclean(fmt, chr);
}

/*
**	v[2]:		0: exp		1: is_long
*/

void			conv_d_efgh(t_fmt *fmt, t_chr **chr, va_list ap)
{
	t_double	db;
	int			v[2];

	v[1] = (fmt->cap_l) ? 1 : 0;
	flag_star(fmt, ap);
	db.d = (flag_dollar(fmt)) ?
			va_arg(*(fmt->arglist), double) : va_arg(ap, double);
	(fmt->precis == -1) ? fmt->precis = 6 : 0;
	if (ft_strchr("fH", fmt->convers))
		(v[1]) ? conv_llf(fmt, chr, ap, 0) : conv_lfh(fmt, chr, db, 0);
	else if (ft_strchr("eE", fmt->convers))
		(v[1]) ? conv_lee(fmt, chr, ap, 0) : conv_ee(fmt, chr, db, 0);
	else
	{
		(fmt->dash) ? fmt->precis = 6 : 0;
		v[0] = int_exp(db.zone.mantissa, (v[1]) ? LD_BIAS : D_BIAS);
		if (v[0] < -4 || v[0] >= (int)(fmt->precis))
		{
			(fmt->convers == 'G') ? fmt->convers = 'E' : 0;
			(v[1]) ? conv_lee(fmt, chr, ap, 1) : conv_ee(fmt, chr, db, 1);
		}
		else
			(v[1]) ? conv_llf(fmt, chr, ap, 1) : conv_lfh(fmt, chr, db, 1);
		efgh_annex(chr, fmt);
	}
}
