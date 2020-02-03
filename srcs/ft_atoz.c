#include "libft.h"

size_t		ft_atoz(const char *str)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
		str[i] == '\f' || str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]))
			n = (n * 10) + (str[i] - 48);
		else
			break ;
		i++;
	}
	return (n);
}
