#include "libft.h"

void	reset_tab_int(int *tab, int size, int n)
{
	int		i;

	i = 0;
	while (i < size)
	{
		tab[i] = n;
		i++;
	}
}
