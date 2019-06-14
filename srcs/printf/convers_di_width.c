/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_di_width.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 06:28:10 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 06:44:53 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		w_di_annex(char **res, t_fmt *fmt, char *nbr, int len)
{
	int			i;

	if (fmt->minus)
	{
		i = -1;
		while (++i < len)
			(*res)[i] = nbr[i];
		while (i < fmt->width)
			(*res)[i++] = ' ';
		return (1);
	}
	return (0);
}

/*
**	v[3]:		0:i		1:j		2:z
*/

char			*width_di(t_fmt *fmt, char *nbr, int len_nbr, int sign)
{
	char		*res;
	int			v[3];
	char		c;

	v[2] = (sign == 0) ? 1 : -1;
	res = (char*)malloc(sizeof(char) * (fmt->width + 1));
	res[fmt->width] = '\0';
	if (w_di_annex(&res, fmt, nbr, len_nbr) == 1)
		return (res);
	c = (fmt->zero && (fmt->precis == v[2])) ? '0' : ' ';
	v[0] = fmt->width - 1;
	v[1] = len_nbr - 1;
	while (v[1] >= 0)
		res[(v[0])--] = nbr[(v[1])--];
	while (v[0] >= 0)
		res[(v[0])--] = c;
	if (c == '0' && (fmt->plus || fmt->space || sign == -1))
	{
		if (sign == -1)
			res[0] = '-';
		else
			res[0] = (fmt->plus) ? '+' : ' ';
		res[fmt->width - len_nbr] = '0';
	}
	return (res);
}
