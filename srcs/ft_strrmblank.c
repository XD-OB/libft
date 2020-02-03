/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrmblank.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelouch <OB-96@hotmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 06:33:31 by obelouch          #+#    #+#             */
/*   Updated: 2020/01/30 06:34:01 by obelouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		new_len(char *str)
{
	size_t		len;
	size_t		i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (!ft_isblank(str[i]))
			len++;
		i++;
	}
	return (len);
}

char			*ft_strrmblank(char *str)
{
	char		*clean;
	size_t		len;
	size_t		i;
	size_t		j;

	len = new_len(str);
	clean = ft_strnew(len);
	i = 0;
	j = 0;
	while (j < len)
	{
		if (!ft_isblank(str[i]))
			clean[j++] = str[i];
		i++;
	}
	return (clean);
}
