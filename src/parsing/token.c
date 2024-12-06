/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:58:18 by neleon            #+#    #+#             */
/*   Updated: 2024/12/06 12:41:21 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int to_handle_quotes(char *line, int i, t_fullcmd *token)
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
    if (line[i] && !is_whitespace(line[i]))
        token->concat_next = true;
    else
        token->concat_next = false;

    return (i);
}


// int	to_handle_quotes(char *line, int i, t_fullcmd *token)
// {
// 	char	quote_type;
// 	int		word_start;

// 	word_start = i;
// 	quote_type = line[i];
// 	i++;
// 	while (line[i] && line[i] != quote_type)
// 		i++;
// 	if (line[i] == quote_type)
// 		i++;
// 	token->type = WORD;
// 	token->str = gc_mem(MALLOC, i - word_start + 1, NULL);
// 	ft_strlcpy(token->str, line + word_start, i - word_start + 1);
// 	return (i);
// }

int	to_handle_pipe(char *line, int i, t_fullcmd *token)
{
	token->type = PIPE;
	token->str = gc_mem(MALLOC, 2, NULL);
	token->str[0] = line[i];
	token->str[1] = '\0';
	return (i + 1);
}
int	to_handle_in(char *line, int i, t_fullcmd *token)
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

int	to_handle_out(char *line, int i, t_fullcmd *token)
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

void	skip_var_name(char *line, int *i)
{
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'
			|| line[*i] == '?'))
		*i += 1;
}

// void	init_token_expand(t_fullcmd *token)
// {
// 	token->type = EXPAND;
// 	token->str = gc_mem(MALLOC, 1, NULL);
// 	token->str[0] = '\0';
// }

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

char	*extract_var(char *line, int *i, int start)
{
	char	*tmp;

	if (!line[*i] || !is_valid_var_char(line[*i]))
		tmp = gc_strdup("$");
	else
	{
		skip_var_name(line, i);
		tmp = gc_mem(MALLOC, *i - start + 1, NULL);
		ft_strlcpy(tmp, line + start, *i - start + 1);
	}
	return (tmp);
}

// void	update_token_str(t_fullcmd *token, char *tmp)
// {
// 	char	*expand;

// 	expand = gc_strjoin(token->str, tmp);
// 	gc_mem(FREE, 0, token->str);
// 	gc_mem(FREE, 0, tmp);
// 	token->str = expand;
// }

int	sub_handle_expand(char *line, int i, t_fullcmd *token)
{
	int		start;
	char	*tmp;
  char	*expand;

	while (line[i] == '$')
	{
		start = i;
		i++;
		tmp = extract_var(line, &i, start);
		// update_token_str(token, tmp);
    expand = gc_strjoin(token->str, tmp);
	  gc_mem(FREE, 0, token->str);
	  gc_mem(FREE, 0, tmp);
	  token->str = expand;
		if (start == i)
			break ;
	}
	return (i);
}

int	to_handle_expand(char *line, int i, t_fullcmd *token)
{
  token->type = EXPAND;
	token->str = gc_mem(MALLOC, 1, NULL);
	token->str[0] = '\0';
	i = sub_handle_expand(line, i, token);
	return (i);
}

static void set_token_type(t_fullcmd *token, t_bool dollar_found)
{
    if (dollar_found)
        token->type = EXPAND;
    else
        token->type = WORD;
}

// static void set_concat_next(t_fullcmd *token, char *line, int i)
// {
//     if (line[i] && !is_whitespace(line[i]))
//         token->concat_next = true;
//     else
//         token->concat_next = false;
// }

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

// int	to_handle_word(char *line, int i, t_fullcmd *token)
// {
// 	int		start;
// 	t_bool	dollar_found;
// 	char	*token_str;

// 	start = i;
// 	dollar_found = false;
// 	token_str = NULL;
// 	while (line[i] && !is_whitespace(line[i]) && !is_separator(line[i])
// 		&& !isquote(line[i]))
// 	{
// 		if (line[i] == '$')
// 			dollar_found = true;
// 		i++;
// 	}
// 	token_str = gc_mem(MALLOC, i - start + 1, NULL);
// 	ft_strlcpy(token_str, line + start, i - start + 1);
// 	if (dollar_found)
// 		token->type = EXPAND;
// 	else
// 		token->type = WORD;
// 	token->str = token_str;
// 	return (i);
// }

int handle_whitespace(char *line, int i)
{
    while (line[i] && is_whitespace(line[i]))
        i++;
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
		i = handle_whitespace(line, i);
		new_token = create_token(&current_token, &head);
		i = process_type(line, i, new_token);
		current_token = new_token;
	}
	data->token_fullcmd = head;
	return (head);
}


// int	to_handle_word(char *line, int i, t_fullcmd *token)
// {
// 	int	word_start;

// 	word_start = i;
// 	while (line[i] && !is_whitespace(line[i]) && !is_separator(line[i])
// 		&& !isquote(line[i]))
// 		i++;
// 	token->str = gc_mem(MALLOC, i - word_start + 1, NULL);
// 	ft_strlcpy(token->str, line + word_start, i - word_start + 1);
// 	token->type = WORD;
// 	return (i);
// }

// int	to_handle_expand(char *line, int i, t_fullcmd *token)
// {
// 	int		start;
// 	char	*tmp;
// 	char	*expand;

// 	start = i;
// 	token->type = EXPAND;
// 	token->str = gc_mem(MALLOC, 1, NULL);
// 	token->str[0] = '\0';
// 	while (line[i] == '$')
// 	{
// 		start = i;
// 		i++;
// 		if (!line[i] || !(ft_isalnum(line[i]) || line[i] == '_'
// 				|| line[i] == '?'))
// 			tmp = gc_strdup("$");
// 		else
// 		{
// 			skip_var_name(line, &i);
// 			tmp = gc_mem(MALLOC, i - start + 1, NULL);
// 			ft_strlcpy(tmp, line + start, i - start + 1);
// 		}
// 		expand = gc_strjoin(token->str, tmp);
// 		gc_mem(FREE, 0, token->str);
// 		gc_mem(FREE, 0, tmp);
// 		token->str = expand;
// 		if (start == i)
// 			break ;
// 	}
// 	return (i);
// }

// int	to_handle_expand(char *line, int i, t_fullcmd *token)
// {
// 	int	start;

// 	start = i;
// 	i++;
// 	skip_var_name(line, &i);
// 	if (i == start + 1)
// 	{
// 		token->type = EXPAND;
// 		token->str = gc_mem(MALLOC, 2, NULL);
// 		token->str[0] = '$';
// 		token->str[1] = '\0';
// 		return (i);
// 	}
// 	token->type = EXPAND;
// 	token->str = gc_mem(MALLOC, i - start + 1, NULL);
// 	ft_strlcpy(token->str, line + start, i - start + 1);
//   start = i;
//   if (line[i] == EXPAND)
//   {
//       skip_var_name(line, &i);
//       if (i == start + 1)
//           gc_strjoin(token->str, "$");
//       else
//           gc_strjoin(token->str, line + start);
//   }
// 	return (i);
// }
