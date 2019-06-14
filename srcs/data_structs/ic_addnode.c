#include "libft.h"

void			ic_addnode(t_icase **icase, int value)
{
	t_icase		*node;

	node = (*icase)->next;
	if (!(node = (t_icase*)malloc(sizeof(t_icase))))
		return ;
	node->n = value;
	node->next = NULL;
}
