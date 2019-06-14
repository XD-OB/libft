/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_ld.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 03:59:42 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/18 07:52:54 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	v[2]:		0: new_exp		1: bin_mantis
*/

char				*get_fractld(long exp, t_ldouble db, t_fmt *format)
{
	int				len_b;
	unsigned int	size;
	char			*binary;
	long			v[2];
	t_icase			*icase;

	size = 0;
	icase = NULL;
	binary = NULL;
	v[0] = (exp == 0) ? 1 - LD_BIAS : exp - LD_BIAS;
	v[1] = db.zone.mantissa;
	len_b = ABS(63 - v[0] - 1);
	if (len_b < 0)
		return (ft_strdup("0"));
	while (len_b >= 0)
	{
		if (fill_tab(&icase, &v[0], exp))
			((v[1] >> len_b) & 1) ? ic_pushnode(&icase, 1) :
									ic_pushnode(&icase, 0);
		size++;
		len_b--;
	}
	binary = ic_joinstr(&icase, size);
	calcul_fract(&binary, size, format);
	return (binary);
}

/*
**	v[2]:		0: len			1: carry
*/

static void			double_free(char **s1, char **s2)
{
	free(*s1);
	free(*s2);
}

void				conv_llf(t_fmt *fmt, t_chr **chr, va_list ap, int is_g)
{
	t_ldouble		db;
	long			v[2];
	char			*fract;
	char			*entier;

	v[1] = 0;
	flag_star(fmt, ap);
	db.ld = (flag_dollar(fmt)) ?
		va_arg(*(fmt->arglist), long double) : va_arg(ap, long double);
	(fmt->precis == -1) ? fmt->precis = 6 : 0;
	if (pre_ld_calc(db, chr, fmt, is_g))
		return ;
	entier = get_entierld(int_exp(db.zone.exponent, LD_BIAS), db, fmt);
	flag_apostrophe(&entier, fmt);
	fract = get_fractld(int_exp(db.zone.exponent, LD_BIAS), db, fmt);
	if (is_g)
		fmt->precis = ft_max(0, (fmt->precis - (long)ft_strlen(entier)));
	fprecis(&fract, fmt->precis, &v[1], 10);
	(v[1] == 1) ? sumstr(&entier, "1", 10) : 0;
	(*chr)->str = ft_pointjoin(fmt, entier, fract, &v[0]);
	(fmt->width > v[0]) ?
		customize_f(fmt, &((*chr)->str), &v[0], db.zone.sign) :
		add_sign_f(fmt, &((*chr)->str), &v[0], db.zone.sign);
	double_free(&entier, &fract);
	(*chr)->len = v[0];
}
