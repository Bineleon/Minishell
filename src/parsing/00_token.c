
#include "../../includes/minishell.h"

t_fullcmd	*create_token(t_fullcmd **current_token, t_fullcmd **head)
{
	t_fullcmd	*new_token;

	new_token = gc_mem(MALLOC, sizeof(t_fullcmd), NULL);
  new_token->concat_next = false;
	new_token->next = NULL;
	if (*current_token)
		(*current_token)->next = new_token;
	else
		*head = new_token;
	return (new_token);
}

