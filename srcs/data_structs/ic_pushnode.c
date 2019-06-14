#include "libft.h"

void			ic_pushnode(t_icase **icase, int value)
{
	t_icase		*node;

	if (!(node = (t_icase*)malloc(sizeof(t_icase))))
		return ;
	node->n = value;
	node->next = (*icase);
	(*icase) = node;
}
