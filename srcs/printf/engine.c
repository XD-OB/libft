/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 17:26:36 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/18 08:15:48 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			semi_load(char *format, t_fmt *fmt, int *p, t_chr **curr)
{
	if (p[1] >= p[0])
	{
		(*curr)->str = cut_str(format, p[0], p[1]);
		(*curr)->len = p[1] - p[0] + 1;
		(*curr)->next = (t_chr*)malloc(sizeof(t_chr));
		(*curr) = (*curr)->next;
		chr_init(curr);
	}
	p[0] = p[1] + 1;
	if (format[p[0]] == '%')
		p[0]++;
	while (format[p[0]] != fmt->convers)
		p[0]++;
	if (fmt->next)
	{
		(*curr)->next = (t_chr*)malloc(sizeof(t_chr));
		(*curr) = (*curr)->next;
		chr_init(curr);
	}
}

char			*strnspdup(char *s, unsigned int *size)
{
	int			len;

	len = ft_strlen(s);
	if (s[len - 1] == '%')
		len--;
	else
	{
		*size = len;
		return (ft_strdup(s));
	}
	*size = len;
	return (ft_strndup(s, len));
}

t_chr			*load_chr(char *format, t_fmt *fmt)
{
	t_chr		*mychr;
	t_chr		*curr;
	int			p[2];

	if (!(mychr = (t_chr*)malloc(sizeof(t_chr))))
		return (0);
	chr_init(&mychr);
	p[0] = 0;
	curr = mychr;
	while (fmt)
	{
		p[1] = fmt->pos - 1;
		semi_load(format, fmt, p, &curr);
		fmt = fmt->next;
		p[0]++;
	}
	if (format[p[0]] && format[p[0]] != '%')
	{
		curr->next = (t_chr*)malloc(sizeof(t_chr));
		curr = curr->next;
		curr->str = strnspdup(&format[p[0]], &(curr->len));
		curr->next = NULL;
	}
	return (mychr);
}

static void		some_convers(t_fmt *fmt, t_chr *chr, va_list ap)
{
	if (fmt->convers == 's')
		conv_s(fmt, &chr, ap);
	else if (fmt->convers == 'c')
		conv_c(fmt, &chr, ap);
	else if (ft_strchr("uU", fmt->convers))
		conv_u(fmt, &chr, ap);
	else if (fmt->convers == 'o')
		conv_o(fmt, &chr, ap);
	else if (fmt->convers == 'k')
		conv_k(&chr, ap);
	else if (fmt->convers == '}')
		conv_color(fmt, &chr);
	else
		conv_percent(&chr, fmt, ap);
}

void			fill_chr(t_fmt *fmt, t_chr *chr, va_list ap)
{
	while (fmt)
	{
		while (chr && chr->str)
			chr = chr->next;
		if (ft_strchr("di", fmt->convers))
			conv_di(fmt, &chr, ap);
		else if (ft_strchr("xX", fmt->convers))
			conv_xx(fmt, &chr, ap);
		else if (ft_strchr("pP", fmt->convers))
			conv_p(fmt, &chr, ap);
		else if (ft_strchr("bB", fmt->convers))
			conv_b(fmt, &chr, ap);
		else if (ft_strchr("uUosck}%", fmt->convers))
			some_convers(fmt, chr, ap);
		else if (ft_strchr("fHeEgG", fmt->convers))
			conv_d_efgh(fmt, &chr, ap);
		else
			conv_invalid(&chr, fmt, ap);
		fmt = fmt->next;
		chr = chr->next;
	}
}
