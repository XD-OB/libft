/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 05:14:25 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/18 08:16:46 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			conv_u_1(t_fmt *fmt, char **str, char *nbr)
{
	char			c;
	int				i;
	size_t			size;

	size = ft_max(ft_strlen(nbr), fmt->width);
	if (!(*str = ft_strnew(size)))
		return (-1);
	c = (fmt->zero && fmt->precis) ? '0' : ' ';
	if (fmt->minus)
	{
		ft_strcpy(*str, nbr);
		i = ft_strlen(nbr);
		while (i < (int)size)
			(*str)[i++] = ' ';
	}
	else
	{
		i = 0;
		while (i < (int)(size - ft_strlen(nbr) + 1))
			(*str)[i++] = c;
		ft_strcpy(&(*str)[--i], nbr);
	}
	return (0);
}

static void			conv_u_2(t_fmt *fmt, char **str, char *nbr, t_chr **mychr)
{
	if (fmt->precis > 0 && fmt->precis < fmt->width)
		precis_u(str, fmt, ft_strlen(nbr));
	else if (fmt->precis >= fmt->width)
	{
		free(*str);
		*str = all_zero_u(nbr, fmt->precis);
	}
	(*mychr)->str = *str;
	free(nbr);
	(*mychr)->len = ft_strlen(*str);
}

/*
**	str[0] = str | str[1] = nbr
*/

void				conv_u(t_fmt *fmt, t_chr **mychr, va_list ap)
{
	char			*str[2];
	unsigned long	n;

	flag_star(fmt, ap);
	n = (flag_dollar(fmt)) ? cast_xxoub(*(fmt->arglist), fmt)
		: cast_xxoub(ap, fmt);
	if (n == 0 && !fmt->precis)
	{
		(*mychr)->str = ft_strcnew(fmt->width, ' ');
		((*mychr)->str)[fmt->width] = '\0';
		(*mychr)->len = fmt->width;
		return ;
	}
	str[1] = ft_ultoa(n);
	flag_apostrophe(&str[1], fmt);
	if (fmt->precis <= 0)
	{
		if (conv_u_1(fmt, &str[0], str[1]) == -1)
			return ;
	}
	else
		str[0] = ft_strdup(str[1]);
	conv_u_2(fmt, &str[0], str[1], mychr);
}
