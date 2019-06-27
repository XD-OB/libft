/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vddnprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 03:27:29 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/18 09:13:07 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** len:		0: len		1: len_format		2: pflag
*/

int			ft_vprintf(const char *format, va_list ap)
{
	t_chr	*mychr;
	t_fmt	*fmt;
	int		len[4];

	len[0] = 0;
	len[1] = 0;
	len[2] = 0;
	while (format[len[1]])
		len[1]++;
	fmt = parse_format(ap, (char*)format, &(len[2]));
	if (!fmt)
	{
		if (len[2] == -1)
			return (0);
		len[3] = put_spstr((char*)format);
		return ((format[len[1] - 1] == '%') ? -1 : len[3]);
	}
	if (!(mychr = load_chr((char*)format, fmt)))
		return (-1);
	fill_chr(fmt, mychr, ap);
	len[0] = put_chr(fmt, mychr);
	free_fmt(&fmt);
	chr_free(&mychr);
	va_end(ap);
	return (len[0]);
}

static int	dprintf_null(char *format, int *len)
{
	int		l;

	if (len[2] == -1)
		return (0);
	l = put_spstr((char*)format);
	return ((format[len[1] - 1] == '%') ? -1 : l);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	t_chr	*mychr;
	t_fmt	*fmt;
	va_list	ap;
	int		len[3];

	len[0] = 0;
	len[1] = -1;
	len[2] = 0;
	while (format[len[1]])
		len[1]++;
	va_start(ap, format);
	fmt = parse_format(ap, (char*)format, &(len[2]));
	if (!fmt)
		return (dprintf_null((char*)format, len));
	if (!(mychr = load_chr((char*)format, fmt)))
		return (-1);
	fill_chr(fmt, mychr, ap);
	len[0] = put_chr_fd(fd, fmt, mychr);
	free_fmt(&fmt);
	chr_free(&mychr);
	va_end(ap);
	return (len[0]);
}

static int	dprintf_null_n(char *format, int *len, size_t n)
{
	if (len[2] == -1)
		return (0);
	put_spstrn((char*)format, n);
	return ((format[len[1] - 1] == '%') ? -1 : n);
}

int			ft_dnprintf(int fd, size_t n, const char *format, ...)
{
	t_chr	*mychr;
	t_fmt	*fmt;
	va_list	ap;
	int		len[3];

	len[0] = 0;
	len[1] = 0;
	len[2] = 0;
	while (format[len[1]])
		len[1]++;
	va_start(ap, format);
	fmt = parse_format(ap, (char*)format, &(len[2]));
	if (!fmt)
		return (dprintf_null_n((char*)format, len, n));
	if (!(mychr = load_chr((char*)format, fmt)))
		return (-1);
	fill_chr(fmt, mychr, ap);
	len[0] = put_chr_nfd(fd, n, mychr);
	free_fmt(&fmt);
	chr_free(&mychr);
	va_end(ap);
	return (len[0]);
}
