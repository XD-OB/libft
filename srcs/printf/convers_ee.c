/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_ee.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:48:46 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 12:46:52 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	new[2]:		new[0]: new_entier	new[1]: new_fract
** 	len[5]:	0: len_e	1: len_f	2: pos   3: len   4:carry
*/

static void		addj_annex(char **n, char **entier, char **fract, long *l)
{
	ft_strswap(entier, &(n[0]));
	ft_strswap(fract, &(n[1]));
	free(n[0]);
	free(n[1]);
	*l = ft_strlen(*fract);
}

static int		addjust_ee(char **entier, char **fract, long *len)
{
	char		*new[2];
	long		i;
	long		p;

	if ((*entier)[0] != '0' && len[0] == 1)
		return (0);
	len[1] = ft_strlen(*fract);
	if (len[0] > 1)
	{
		new[0] = ft_strcnew(1, (*entier)[0]);
		new[1] = ft_strjoin(&(*entier)[1], *fract);
	}
	else
	{
		i = 0;
		while ((*fract)[i] == '0')
			i++;
		new[0] = ft_strcnew(1, (*fract)[i]);
		new[1] = ft_strdup(&(*fract)[++i]);
	}
	addj_annex(new, entier, fract, &i);
	p = (len[0] > 1) ? (len[0] - 1) : (i - len[1]);
	len[0] = 1;
	len[1] = i;
	return (p);
}

void			weapon_ee(char **entier, char **fract, long *len, int x)
{
	char		*tmp;

	if (!x)
	{
		if (len[4] == 1)
		{
			tmp = *entier;
			*entier = ft_strsum(tmp, "1", 10);
			if (ft_strlen(*entier) > 1)
			{
				tmp = *entier;
				*entier = ft_strndup(*entier, 1);
				if (len[3] >= 0)
					len[2]++;
				else
					len[2]--;
			}
			free(tmp);
		}
		return ;
	}
	len[4] = 0;
	len[0] = ft_strlen(*entier);
	len[1] = ft_strlen(*fract);
	len[2] = addjust_ee(entier, fract, len);
}

void			conv_ee(t_fmt *fmt, t_chr **chr, t_double db, int is_g)
{
	char		*entier;
	char		*fract;
	long		len[5];

	if (pre_d_calc(db, chr, fmt, is_g))
		return ;
	entier = get_entier(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, fmt);
	fract = get_fract(int_exp(db.zone.exponent, D_BIAS),
			db.zone.mantissa, D_BIAS, fmt);
	weapon_ee(&entier, &fract, len, 1);
	(is_g) ? fmt->precis = ft_max(0, (fmt->precis - len[0])) : 0;
	eprecis(&fract, fmt->precis, &len[4], &len[1]);
	weapon_ee(&entier, &fract, len, 0);
	(*chr)->str = ejoin(fmt, entier, fract, len);
	(fmt->width > len[3]) ?
		customize_f(fmt, &((*chr)->str), &len[3], db.zone.sign) :
		add_sign_f(fmt, &((*chr)->str), &len[3], db.zone.sign);
	(*chr)->len = len[3];
	free(entier);
	free(fract);
}

void			conv_lee(t_fmt *fmt, t_chr **chr, va_list ap, int is_g)
{
	t_ldouble	db;
	char		*entier;
	char		*fract;
	long		len[5];

	flag_star(fmt, ap);
	db.ld = (flag_dollar(fmt)) ?
		va_arg(*(fmt->arglist), long double) : va_arg(ap, long double);
	(fmt->precis == -1) ? fmt->precis = 6 : 0;
	if (pre_ld_calc(db, chr, fmt, is_g))
		return ;
	entier = get_entierld(int_exp(db.zone.exponent, LD_BIAS), db, fmt);
	fract = get_fractld(int_exp(db.zone.exponent, LD_BIAS), db, fmt);
	weapon_ee(&entier, &fract, len, 1);
	(is_g) ? fmt->precis = ft_max(0, (fmt->precis - len[0])) : 0;
	eprecis(&fract, fmt->precis, &len[4], &len[1]);
	weapon_ee(&entier, &fract, len, 0);
	(*chr)->str = ejoin(fmt, entier, fract, len);
	(fmt->width > len[3]) ?
		customize_f(fmt, &((*chr)->str), &len[3], db.zone.sign) :
		add_sign_f(fmt, &((*chr)->str), &len[3], db.zone.sign);
	(*chr)->len = len[3];
	free(entier);
	free(fract);
}
