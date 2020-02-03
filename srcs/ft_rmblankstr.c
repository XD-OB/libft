#include "libft.h"

void		ft_rmblankstr(char **str)
{
	char	*tmp;

	tmp = ft_strrmblank(*str);
	free(*str);
	*str = tmp;
}
