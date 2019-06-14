/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_pcolinv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:20:38 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 17:26:49 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		conv_invalid(t_chr **mychr, t_fmt *format, va_list ap)
{
	int		i;

	flag_star(format, ap);
	i = -1;
	if (!format->width)
	{
		(*mychr)->str = ft_strnew(1);
		(*mychr)->str[0] = format->convers;
		(*mychr)->len = 1;
	}
	else
	{
		(*mychr)->str = ft_strnew(format->width);
		while (++i < format->width - 1)
			(*mychr)->str[i] = ' ';
		(*mychr)->str[i] = format->convers;
		(*mychr)->len = format->width;
	}
}

static int	conv_bold_color(t_fmt *fmt, t_chr **mychr)
{
	if (!ft_strcmp(fmt->color, "RED"))
		(*mychr)->str = ft_strdup(B_RED);
	else if (!ft_strcmp(fmt->color, "GREEN"))
		(*mychr)->str = ft_strdup(B_GREEN);
	else if (!ft_strcmp(fmt->color, "YELLOW"))
		(*mychr)->str = ft_strdup(B_YELLOW);
	else if (!ft_strcmp(fmt->color, "BLUE"))
		(*mychr)->str = ft_strdup(B_BLUE);
	else if (!ft_strcmp(fmt->color, "PURPLE"))
		(*mychr)->str = ft_strdup(B_PURPLE);
	else if (!ft_strcmp(fmt->color, "CYAN"))
		(*mychr)->str = ft_strdup(B_CYAN);
	else
		return (0);
	return (1);
}

void		conv_color(t_fmt *fmt, t_chr **mychr)
{
	(*mychr)->len = 0;
	if (conv_bold_color(fmt, mychr))
		return ;
	if (!ft_strcmp(fmt->color, "red"))
		(*mychr)->str = ft_strdup(RED);
	else if (!ft_strcmp(fmt->color, "green"))
		(*mychr)->str = ft_strdup(GREEN);
	else if (!ft_strcmp(fmt->color, "yellow"))
		(*mychr)->str = ft_strdup(YELLOW);
	else if (!ft_strcmp(fmt->color, "blue"))
		(*mychr)->str = ft_strdup(BLUE);
	else if (!ft_strcmp(fmt->color, "purple"))
		(*mychr)->str = ft_strdup(PURPLE);
	else if (!ft_strcmp(fmt->color, "cyan"))
		(*mychr)->str = ft_strdup(CYAN);
	else if (!ft_strcmp(fmt->color, "eoc"))
		(*mychr)->str = ft_strdup(EOC);
	else
	{
		(*mychr)->str = ft_strdup(fmt->color);
		(*mychr)->len = ft_strlen((*mychr)->str);
	}
}

void		conv_percent(t_chr **mychr, t_fmt *fmt, va_list ap)
{
	char	*str;
	int		len;
	int		i;
	char	c;

	flag_star(fmt, ap);
	len = ft_max(1, fmt->width);
	str = ft_strnew(len);
	c = (fmt->zero) ? '0' : ' ';
	if (fmt->minus)
	{
		str[0] = '%';
		i = 0;
		while (++i < len)
			str[i] = ' ';
	}
	else
	{
		i = -1;
		while (++i < len - 1)
			str[i] = c;
		str[len - 1] = '%';
	}
	(*mychr)->str = str;
	(*mychr)->len = len;
}
