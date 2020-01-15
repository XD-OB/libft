#include "libft.h"

char			*ft_strcjoin(const char *str, char c)
{
	char		*res;
	size_t		len;
	size_t		i;

	len = ft_strlen(str);
	res = ft_strcnew(len + 1, c);
	if (str)
	{
		i = 0;
		while (i < len)
		{
			res[i] = str[i];
			i++;
		}
	}
	return (res);
}
