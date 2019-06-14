/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precalc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 09:27:28 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/18 08:26:52 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char			*ft_strzero(t_fmt *fmt, long *len, int is_g, long sign)
{
	char			*res;
	char			*tmp;

	if (is_g && (!fmt->dash || !fmt->precis))
		*len = 1;
	else
	{
		(is_g) ? fmt->precis = ft_max(fmt->precis - 1, 0) : 0;
		*len = fmt->precis + 1;
	}
	(*len > 1 || fmt->dash) ? (*len)++ : 0;
	res = ft_strcnew(*len, '0');
	if (*len > 1)
		res[1] = '.';
	if (ft_strchr("eE", fmt->convers))
	{
		tmp = ft_strjoin(res, "e+00");
		free(res);
		res = tmp;
		*len += 4;
	}
	(fmt->width > *len) ? customize_f(fmt, &res, len, sign)
						: add_sign_f(fmt, &res, len, sign);
	return (res);
}

static char			*precalc_inf(t_fmt *fmt, long *len, long sign)
{
	char			*str;

	str = (fmt->convers < 97) ? ft_strdup("INF") : ft_strdup("inf");
	*len = 3;
	if (fmt->width > *len)
		custom_inff(fmt, &str, len, sign);
	else
		add_sign_f(fmt, &str, len, sign);
	return (str);
}

int					pre_d_calc(t_double db, t_chr **chr, t_fmt *fmt, int is_g)
{
	char			*str;
	long			len;

	len = INT_MIN;
	if (!int_mants(db.zone.mantissa, D_BIAS) &&
		!int_exp(db.zone.exponent, D_BIAS))
		str = ft_strzero(fmt, &len, is_g, db.zone.sign);
	else if (!int_mants(db.zone.mantissa, D_BIAS) &&
			(int_exp(db.zone.exponent, D_BIAS) >= MAX_D))
		str = precalc_inf(fmt, &len, db.zone.sign);
	else if (int_mants(db.zone.mantissa, D_BIAS) &&
		(int_exp(db.zone.exponent, D_BIAS) >= MAX_D))
	{
		str = (fmt->convers < 97) ? ft_strdup("NAN") : ft_strdup("nan");
		len = 3;
		(fmt->width > len) ? custom_nanf(fmt, &str, &len) : 0;
	}
	if (len == INT_MIN)
		return (0);
	(*chr)->str = str;
	(*chr)->len = len;
	return (1);
}

int					pre_ld_calc(t_ldouble db, t_chr **chr, t_fmt *fmt, int is_g)
{
	char			*str;
	long			len;

	len = INT_MIN;
	(is_g) ? fmt->precis = ft_max(fmt->precis - 1, 0) : 0;
	if (!int_mants(db.zone.mantissa, LD_BIAS) &&
		!int_exp(db.zone.exponent, LD_BIAS))
		str = ft_strzero(fmt, &len, is_g, db.zone.sign);
	else if (!int_mants(db.zone.mantissa, LD_BIAS) &&
			(int_exp(db.zone.exponent, LD_BIAS) >= MAX_LD))
		str = precalc_inf(fmt, &len, db.zone.sign);
	else if (int_mants(db.zone.mantissa, LD_BIAS) &&
		(int_exp(db.zone.exponent, LD_BIAS) >= MAX_LD))
	{
		str = ft_strdup("nan");
		len = 3;
		(fmt->width > len) ? custom_nanf(fmt, &str, &len) : 0;
	}
	if (len == INT_MIN)
		return (0);
	(*chr)->str = str;
	(*chr)->len = len;
	return (1);
}
