

#include "../../includes/minishell.h"

int skip_whitespaces(char *line, int i)
{
    while (line[i] && is_whitespace(line[i]))
        i++;
    return (i);
}

static void set_token_type(t_fullcmd *token, t_bool dollar_found)
{
    if (dollar_found)
        token->type = EXPAND;
    else
        token->type = WORD;
}

int to_handle_word(char *line, int i, t_fullcmd *token)
{
    int start;
    t_bool dollar_found;
    char *token_str;

    start = i;
    dollar_found = false;
    token_str = NULL;
    while (line[i] && !is_whitespace(line[i])
          && !is_separator(line[i]) && !isquote(line[i]))
    {
        if (line[i] == '$')
            dollar_found = true;
        i++;
    }
    token_str = gc_mem(MALLOC, i - start + 1, NULL);
    ft_strlcpy(token_str, line + start, i - start + 1);
    set_token_type(token, dollar_found);
    token->str = token_str;
    if (line[i] && !is_whitespace(line[i]))
        token->concat_next = true;
    else
        token->concat_next = false;
    return (i);
}

int process_type(char *line, int i, t_fullcmd *new_token)
{
    if (isquote(line[i]))
        i = to_handle_quotes(line, i, new_token);
    else if (line[i] == PIPE)
        i = to_handle_pipe(line, i, new_token);
    else if (line[i] == IN)
        i = to_handle_in(line, i, new_token);
    else if (line[i] == OUT)
        i = to_handle_out(line, i, new_token);
    else if (line[i] == EXPAND)
        i = to_handle_expand(line, i, new_token);
    else
        i = to_handle_word(line, i, new_token);
    return (i);
}

t_fullcmd	*parse_tokens(char *line, t_data *data)
{
	t_fullcmd	*head;
	t_fullcmd	*current_token;
	t_fullcmd	*new_token;
	int			i;

	i = 0;
	head = NULL;
	current_token = NULL;
	while (line[i])
	{
		i = skip_whitespaces(line, i);
		new_token = create_token(&current_token, &head);
		i = process_type(line, i, new_token);
		current_token = new_token;
	}
	data->token_fullcmd = head;
	return (head);
}
