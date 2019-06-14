/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gets.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 13:34:52 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/18 07:52:36 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char				*get_entier(long exp, long bin_mantis, int bias,
							t_fmt *format)
{
	unsigned long long	m;
	unsigned int		v[2];
	long				new_exp;
	char				*binary;
	t_icase				*icase;

	v[0] = 1;
	v[1] = 0;
	binary = NULL;
		icase = NULL;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	if (new_exp < 0)
		return (ft_strdup("0"));
	m = 2251799813685248;
	(exp) ? ic_pushnode(&icase, 1) : ic_pushnode(&icase, 0);
	while ((v[1])++ < new_exp)
	{
		(m & bin_mantis) ? ic_pushnode(&icase, 1) : ic_pushnode(&icase, 0);
		v[0]++;
		m >>= 1;
	}
	binary = ic_joinstr(&icase, v[0]);
	calcul_entier(&binary, v[0], format);
	return (binary);
}

int					fill_tab(t_icase **icase, long *new_exp, long exp)
{
	if (*new_exp < -1)
	{
		ic_pushnode(icase, 0);
		(*new_exp)++;
		return (0);
	}
	if (*new_exp == -1)
	{
		(exp) ? ic_pushnode(icase, 1) : ic_pushnode(icase, 0);
		(*new_exp)++;
		return (0);
	}
	return (1);
}

char				*get_fract(long exp, long bin_mantis, int bias,
							t_fmt *format)
{
	unsigned int	size;
	long			new_exp;
	int				len_b;
	char			*binary;
	t_icase			*icase;

	size = 0;
	icase = NULL;
	binary = NULL;
	new_exp = (exp == 0) ? 1 - bias : exp - bias;
	len_b = ABS(52 - new_exp - 1);
	if (len_b < 0)
		return (ft_strdup("0"));
	while (len_b >= 0)
	{
		if (fill_tab(&icase, &new_exp, exp))
			((bin_mantis >> len_b) & 1) ?
				ic_pushnode(&icase, 1) : ic_pushnode(&icase, 0);
		size++;
		len_b--;
	}
	binary = ic_joinstr(&icase, size);
	calcul_fract(&binary, size, format);
	return (binary);
}

void			get_eld_annex(t_icase **icase, unsigned int *size, long new_exp)
{
	while (new_exp > 0)
	{
		ic_pushnode(icase, 0);
		(*size)++;
		new_exp--;
	}
}

/*
**	v[2]:	0: bin_mantis		1: new_exp
*/

char				*get_entierld(long exp, t_ldouble db, t_fmt *format)
{
	long			v[2];
	char			*binary;
	unsigned int	size;
	int				i;
	t_icase			*icase;

	binary = NULL;
	icase = NULL;
	size = 1;
	v[0] = db.zone.mantissa;
	v[1] = (exp == 0) ? 1 - LD_BIAS : exp - LD_BIAS;
	if (v[1] < 0)
		return (ft_strdup("0"));
	(db.zone.int_b) ? ic_pushnode(&icase, 1) : ic_pushnode(&icase, 0);
	i = 63;
	while (--i >= 0 && v[1] > 0)
	{
		(1 & (v[0] >> i)) ?
			ic_pushnode(&icase, 1) : ic_pushnode(&icase, 0);
		size++;
		v[1]--;
	}
	get_eld_annex(&icase, &size, v[1]);
	binary = ic_joinstr(&icase, size);
	calcul_entier(&binary, size, format);
	return (binary);
}
