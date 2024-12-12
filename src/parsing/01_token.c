/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:11:58 by neleon            #+#    #+#             */
/*   Updated: 2024/12/12 16:12:01 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	to_handle_quotes(char *line, int i, t_fullcmd *token)
{
	char	quote_type;
	int		word_start;

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
	if (line[i] && !is_whitespace(line[i]))
		token->concat_next = true;
	else
		token->concat_next = false;
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
