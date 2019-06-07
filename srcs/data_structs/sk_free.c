#include "libft.h"

void	sk_free(t_list **head)
{
	t_list	*tmp;

	while (*head)
	{
		tmp = *head;
		if ((*head)->content)
			free((*head)->content);
		*head = (*head)->next;
		free(tmp);
	}
}
