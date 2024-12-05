
#include "../../includes/minishell.h"

void	handle_squote_exp(t_fullcmd *token)
{
	char	*tmp;
	char	*result;
	int		i;
	int		j;

	i = 1;
	j = 0;
	tmp = gc_mem(MALLOC, ft_strlen(token->str) + 1, NULL);
	result = gc_mem(MALLOC, 1, NULL);
	result[0] = '\0';
	while (token->str[i] && token->str[i] != SQUOTE)
		tmp[j++] = token->str[i++];
	tmp[j] = '\0';
	result = gc_strjoin(result, tmp);
	gc_mem(FREE, 0, token->str);
	token->str = result;
	gc_mem(FREE, 0, tmp);
}

void concat_tokens(t_fullcmd *head)
{
    t_fullcmd *current;
    t_fullcmd *to_free;
     char *new_str;

    current = head;
    to_free = NULL;
    while (current && current->next)
    {
        if (current->concat_next && current->next->type == WORD)
        {
            new_str = gc_strjoin(current->str, current->next->str);
            gc_mem(FREE, 0, current->str);
            current->str = new_str;
            to_free = current->next;
            current->next = current->next->next;
            gc_mem(FREE, 0, to_free->str);
            gc_mem(FREE, 0, to_free);
            current->concat_next = false;
        }
        else
            current = current->next;
    }
}

void expand_var(t_data *data)
{
    t_fullcmd *current;

    current = data->token_fullcmd;
    while (current)
    {
        if (current->type == EXPAND)
            handle_expand(current, data->envp_cpy);
        else if (current->type == WORD && is_in_dquote(current))
            handle_dquote_exp(current, data->envp_cpy);
        else if (current->type == WORD && is_in_squote(current))
            handle_squote_exp(current);
        current = current->next;
    }
    concat_tokens(data->token_fullcmd);
}
