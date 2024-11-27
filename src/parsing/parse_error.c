/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:57:05 by neleon            #+#    #+#             */
/*   Updated: 2024/11/27 15:15:54 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void    print_syntax_error(char *str)
{
    ft_putstr_fd("syntax error near unexpected token ", 2);
    ft_putstr_fd(str, 2);
}

t_bool	check_open_quotes(char *line)
{
	t_bool	dq;
	t_bool	sq;
	int		i;

	i = 0;
	dq = false;
	sq = false;
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
		ft_putstr_fd("minishell: error: open quote\n", 2);
		return (true);
	}
	return (false);
}

t_bool	pipe_errors(t_fullcmd *tokens)
{
	t_fullcmd	*current;

	current = tokens;
	if (current && current->type == PIPE)
		return (print_syntax_error("`newline'\n"), true);
	while (current)
	{
		if (current->type == PIPE)
		{
			if (!current->next)
				return (print_syntax_error("`|'\n"), true);
			else
			{
				if (current->next->type != WORD || current->next->type == PIPE)
					return (print_syntax_error("`|'\n"), true);
			}
		}
		current = current->next;
	}
	return (false);
}

t_bool	sub_redirect_errors(t_fullcmd *tokens)
{
	if (!tokens->next || tokens->next->type != WORD)
	{
		if (tokens->type == IN || tokens->type == OUT)
			print_syntax_error("`newline'\n");
		if (tokens->type == APPEND)
			print_syntax_error("`<<'\n");
		if (tokens->type == HEREDOC)
			print_syntax_error("`>>'\n");
		return (true);
	}
	return (false);
}

t_bool	redirect_errors(t_fullcmd *tokens)
{
	t_fullcmd	*current;

	current = tokens;
	if (current && (current->type == IN || current->type == OUT
			|| current->type == APPEND || current->type == HEREDOC)
		&& !current->next)
	{
		print_syntax_error("`newline'\n");
		return (true);
	}
	while (current)
	{
		sub_redirect_errors(current);
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
  t_data  *data;

  data = get_data();
	if (pipe_errors(tokens) || redirect_errors(tokens))
  {
    data->exit_status = 2;
		return (true);
  }
  data->exit_status = 0;
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
