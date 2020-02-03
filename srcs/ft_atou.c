#include "libft.h"

unsigned int		ft_atou(const char *str)
{
	unsigned int	n;
	size_t		i;

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
