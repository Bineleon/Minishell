/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:57:05 by neleon            #+#    #+#             */
/*   Updated: 2024/12/04 18:18:01 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_open_quotes(char *line)
{
	t_bool	dq;
	t_bool	sq;
	t_data	*data;
	int		i;

	i = 0;
	dq = false;
	sq = false;
	data = get_data();
	while (line[i])
	{
		if (line[i] == SQUOTE && !dq)
			sq = !sq;
		else if (line[i] == DQUOTE && !sq)
			dq = !dq;
		i++;
	}
	if (dq || sq)
	{
		// ft_putstr_fd("minishell: error: open quote\n", 2);
		data->exit_status = 1;
		return (true);
	}
	return (false);
}

t_bool check_unexpected_tok(t_fullcmd *tokens)
{
	t_fullcmd *current;

	current = tokens;
	if (current	&& !ft_isalnum(current->str[0])
		&& !is_separator(current->str[0]) && current->str[0] != '$')
		return (error_syntax(current->str), true);
	return (false);
}

t_bool	first_pipe_err(t_fullcmd *token)
{
	if (token && token->type == PIPE && token->next)
	{
		if (token->next->type == PIPE)
			return (error_syntax("||"), true);
	}
	if (token && token->type == PIPE)
		return (error_syntax("|"), true);
	return (false);
}

t_bool	pipe_errors(t_fullcmd *tokens)
{
	t_fullcmd	*current;

	current = tokens;
	if (first_pipe_err(tokens))
		return (true);
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!current->next)
				return (error_syntax("|"), true);
			else
			{
				if (current->next->type == PIPE)
					return (error_syntax("||"), true);
				if (current->next->type != WORD)
					return (error_syntax("|"), true);
			}
		}
		current = current->next;
	}
	return (false);
}

t_bool	sub_redirect_errors(t_fullcmd *tokens)
{
	if (is_redi(tokens) && (!tokens->next || tokens->next->type != WORD))
	{
		if (tokens->next->type == APPEND)
			error_syntax(">>");
		else if (tokens->next->type == HEREDOC)
			error_syntax("<<");
		else if (tokens->next->type == IN || tokens->next->type == OUT)
			error_syntax("newline");
		return (true);
	}
	return (false);
}

t_bool	is_redi(t_fullcmd *token)
{
	if (token && (token->type == IN || token->type == OUT
			|| token->type == APPEND || token->type == HEREDOC))
		return (true);
	return (false);
}

t_bool	redirect_errors(t_fullcmd *tokens)
{
	t_fullcmd	*current;

	current = tokens;
	if (is_redi(current) && !current->next)
	{
		error_syntax("newline");
		return (true);
	}
	current = current->next;
	while (current)
	{
		if (sub_redirect_errors(current))
			return (true);
		current = current->next;
	}
	return (false);
}

// t_bool	expand_errors(t_fullcmd *tokens)
// {
// 	t_fullcmd	*current;

// 	current = tokens;
// 	while (current)
// 	{
// 		if ((current->type == EXPAND) && (!current->next
// 				|| current->next->type == EXPAND))
// 		{
// 			ft_putstr_fd("minishell: error: expand\n", 2);
// 			return (true);
// 		}
// 		current = current->next;
// 	}
// 	return (false);
// }

t_bool	check_errors(t_fullcmd *tokens)
{
	t_data	*data;

	data = get_data();
	if (pipe_errors(tokens) || redirect_errors(tokens))
	{
		data->exit_status = 2;
		return (true);
	}
	// data->exit_status = 0;
	return (false);
}
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
