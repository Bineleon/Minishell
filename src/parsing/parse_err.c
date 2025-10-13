/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:57:05 by neleon            #+#    #+#             */
/*   Updated: 2024/12/14 00:44:15 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	sub_redirect_errors(t_fullcmd *tokens)
{
	if (is_redi(tokens) && (!tokens->next))
	{
		error_syntax("newline");
		return (true);
	}
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

t_bool	check_errors(t_fullcmd *tokens)
{
	t_data	*data;

	data = get_data();
	if (pipe_errors(tokens) || redirect_errors(tokens))
	{
		data->exit_status = 2;
		return (true);
	}
	return (false);
}
