/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcalcul_dld.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 01:02:57 by obelouch          #+#    #+#             */
/*   Updated: 2019/04/17 18:28:43 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*calc_entier(char *tab, int size, t_fmt *format)
{
	char		*entier;
	char		*count;
	int			debut;
	int			base;
	int			i;

	base = (format->convers == 'H') ? 16 : 10;
	entier = ft_strdup("0");
	debut = 0;
	while (tab[debut] == '0')
		debut++;
	i = size - 1;
	while (i >= debut && tab[i] == '0')
		i--;
	count = ft_strpower(2, (size - i - 1), base);
	while (i >= debut)
	{
		if (tab[i] == '1')
			sumstr(&entier, count, base);
		multstr(&count, "2", base);
		i--;
	}
	free(count);
	return (entier);
}

void			calcul_entier(char **tab, int size, t_fmt *format)
{
	char		*res;

	res = calc_entier(*tab, size, format);
	free(*tab);
	*tab = res;
}

static int		ft_strupdatelen(char *str, int old)
{
	int			len;

	len = old;
	while (str[len])
		len++;
	return (len);
}

/*
**	var[3]: 	0: base	   1: len	2: i
*/

static char		*calc_fract(char *tab, int size, t_fmt *fmt)
{
	char		*fract;
	char		*count;
	int			var[3];

	var[1] = 1;
	var[2] = 0;
	var[0] = (fmt->convers == 'H') ? 16 : 10;
	while (var[2] <= size && tab[var[2]] == '0')
		var[2]++;
	count = ft_strpower(5, var[2] + 1, var[0]);
	fract = ft_strcnew(var[2] + 1, '0');
	while (var[2] <= size)
	{
		if (tab[var[2]++] == '1')
		{
			sumstr(&fract, count, var[0]);
			var[1] = ft_strupdatelen(fract, var[1]);
		}
		multstr(&count, "5", var[0]);
		foisdix(&fract, &(var[1]));
	}
	free(count);
	return (fract);
}

void			calcul_fract(char **tab, int size, t_fmt *format)
{
	char		*res;

	while ((*tab)[size] == '0')
		size--;
	res = calc_fract(*tab, size - 1, format);
	free(*tab);
	*tab = res;
}
