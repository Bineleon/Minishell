/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:42:36 by neleon            #+#    #+#             */
/*   Updated: 2024/12/14 00:49:06 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			}
		}
		current = current->next;
	}
	return (false);
}
