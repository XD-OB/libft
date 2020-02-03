#include "libft.h"

void		tabstr_rmblank(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		ft_rmblankstr(&tab[i++]);
}
