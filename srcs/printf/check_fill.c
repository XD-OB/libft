/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 05:14:43 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/18 06:51:46 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		put_width_precis(t_fmt *curr, char **str)
{
	if (!**str)
		return (1);
	if (ft_isdigit(**str))
	{
		curr->width = ft_atoi(*str);
		while (ft_isdigit(**str))
			(*str)++;
	}
	if (!**str)
		return (1);
	if (**str == '.')
	{
		(*str)++;
		if (**str == '*')
		{
			curr->precis = -2;
			(*str)++;
		}
		else
			curr->precis = ft_atoi(*str);
		while (ft_isdigit(**str))
			(*str)++;
	}
	return (0);
}

static int		prepare_dollar(t_fmt *curr, char **str, va_list tmp)
{
	curr->dollar = 1;
	(*str)++;
	curr->arglist = (va_list*)malloc(sizeof(va_list));
	va_copy(*(curr->arglist), tmp);
	curr->argn = ft_atoi(*str);
	while (ft_isdigit(**str))
		(*str)++;
	return (1);
}

int				put_preflag(t_fmt *curr, char **str, char flag, va_list tmp)
{
	if (flag == '$')
		return (prepare_dollar(curr, str, tmp));
	if (flag == '0')
		curr->zero = 1;
	else if (flag == '#')
		curr->dash = 1;
	else if (flag == ' ')
		curr->space = 1;
	else if (flag == '-')
		curr->minus = 1;
	else if (flag == '+')
		curr->plus = 1;
	else if (flag == '\'')
		curr->quote = 1;
	else if (flag == '*')
		curr->star = 1;
	else if (flag == 'r')
		curr->r = 1;
	else
		return (0);
	return (1);
}

int				put_postflag(t_fmt *curr, char flag, char next)
{
	if (flag == 'L')
		curr->cap_l = 1;
	else if (flag == 'l')
	{
		if (next == 'l')
			curr->ll = 1;
		else
			curr->l = 1;
	}
	else if (flag == 'h')
	{
		if (next == 'h')
			curr->hh = 1;
		else
			curr->h = 1;
	}
	else if (flag == 'r')
		curr->r = 1;
	else if (flag == 'j')
		curr->j = 1;
	else if (flag == 'z')
		curr->z = 1;
	else
		return (0);
	return (1);
}

int				check_fill(va_list tmp, char *str, int pos, t_fmt *curr)
{
	curr->pos = pos;
	if (*str == '{')
	{
		(*str)++;
		curr->color = ft_strcolor(str);
		curr->convers = '}';
		return (0);
	}
	while (put_preflag(curr, &str, *str, tmp))
		str++;
	if (put_width_precis(curr, &str))
		return (-1);
	if (put_postflag(curr, *str, *(str + 1)))
		str++;
	if (!*str)
		return (1);
	curr->convers = *str;
	return (0);
}
