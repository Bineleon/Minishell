
#include "../../includes/minishell.h"

t_fullcmd *create_new_token(t_fullcmd **current_token, t_fullcmd **head)
{
    t_fullcmd *new_token;

    new_token = gc_mem(MALLOC, sizeof(t_fullcmd), NULL);
    new_token->next = NULL;
    if (*current_token)
        (*current_token)->next = new_token;
    else
        *head = new_token;
    return (new_token);
}

int handle_quotes(char *line, int i, t_fullcmd *token)
{
    char quote_type;
    int word_start;

    word_start = i;
    quote_type = line[i];
    i++;
    while (line[i] && line[i] != quote_type)
        i++;
    if (line[i] == quote_type)
        i++;
    token->type = WORD;
    token->str = gc_mem(MALLOC, i - word_start + 1, NULL);
    ft_strlcpy(token->str, line + word_start, i - word_start + 1);
    return (i);
}

int handle_pipe(char *line, int i, t_fullcmd *token)
{
    token->type = PIPE;
    token->str = gc_mem(MALLOC, 2, NULL);
    token->str[0] = line[i];
    token->str[1] = '\0';
    return (i + 1);
}
int handle_in(char *line, int i, t_fullcmd *token)
{
    if (line[i + 1] == '<')
    {
        token->type = HEREDOC;
        token->str = gc_mem(MALLOC, 3, NULL);
        token->str[0] = line[i];
        token->str[1] = line[i + 1];
        token->str[2] = '\0';
        return (i + 2);
    }
    else
    {
        token->type = IN;
        token->str = gc_mem(MALLOC, 2, NULL);
        token->str[0] = line[i];
        token->str[1] = '\0';
        return (i + 1);
    }
}

int handle_out(char *line, int i, t_fullcmd *token)
{
    if (line[i + 1] == '>')
    {
        token->type = APPEND;
        token->str = gc_mem(MALLOC, 3, NULL);
        token->str[0] = line[i];
        token->str[1] = line[i + 1];
        token->str[2] = '\0';
        return (i + 2);
    }
    else
    {
        token->type = OUT;
        token->str = gc_mem(MALLOC, 2, NULL);
        token->str[0] = line[i];
        token->str[1] = '\0';
        return (i + 1);
    }
}

int handle_expand(char *line, int i, t_fullcmd *token)
{
    token->type = EXPAND;
    token->str = gc_mem(MALLOC, 2, NULL);
    token->str[0] = line[i];
    token->str[1] = '\0';
    return (i + 1);
}

int handle_word(char *line, int i, t_fullcmd *token)
{
    int word_start;

    word_start = i;
    while (line[i] && !is_whitespace(line[i]) && !is_separator(line[i]) && !isquote(line[i]))
        i++;
    token->type = WORD;
    token->str = gc_mem(MALLOC, i - word_start + 1, NULL);
    ft_strlcpy(token->str, line + word_start, i - word_start + 1);
    return (i);
}

t_fullcmd *parse_tokens(char *line, t_data *data)
{
    t_fullcmd *head;
    t_fullcmd *current_token;
    t_fullcmd *new_token;
    int i;

    i = 0;
    head = NULL;
    current_token = NULL;
    while (line[i])
    {
        if (is_whitespace(line[i]))
            i++;
        new_token = create_new_token(&current_token, &head);
        if (isquote(line[i]))
            i = handle_quotes(line, i, new_token);
        else if (line[i] == PIPE)
            i = handle_pipe(line, i, new_token);
        else if (line[i] == IN)
            i = handle_in(line, i, new_token);
        else if (line[i] == OUT)
            i = handle_out(line, i, new_token);
        else if (line[i] == EXPAND)
            i = handle_expand(line, i, new_token);
        else
            i = handle_word(line, i, new_token);
        current_token = new_token;
    }
    data->token = head;
    return (head);
}