/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:15:04 by neleon            #+#    #+#             */
/*   Updated: 2024/12/13 13:12:19 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sub_find_cmds(t_bool *is_file, t_bool *is_cmd, t_fullcmd *current)
{
	if (is_redi(current))
		*is_file = true;
	else if (*is_file)
	{
		*is_file = false;
		current->is_cmd = false;
	}
	else if ((current->type == WORD) && *is_cmd == false)
	{
		current->is_cmd = true;
		*is_cmd = true;
	}
	else
		current->is_cmd = *is_cmd;
}

void	find_cmds(t_data *data)
{
	t_fullcmd	*current;
	t_bool		is_cmd;
	t_bool		is_file;

	current = data->token_fullcmd;
	is_file = false;
	is_cmd = false;
	while (current)
	{
		is_cmd = false;
		while (current && current->type != PIPE)
		{
			sub_find_cmds(&is_file, &is_cmd, current);
			current = current->next;
		}
		if (current && current->type == PIPE)
		{
			current->is_cmd = false;
			current = current->next;
		}
	}
}
