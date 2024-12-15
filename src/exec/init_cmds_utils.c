/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:17:29 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/15 15:58:23 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	adding_new_redirs(t_cmd *cmds, t_fullcmd **current)
{
	while ((*current) && (*current)->type != PIPE)
	{
		if (is_redi((*current)))
		{
			if ((*current)->next && (*current)->next->type == WORD)
			{
				add_redir(&cmds->redir, (*current)->type,
					(*current)->next->str);
				(*current) = (*current)->next;
			}
		}
		(*current) = (*current)->next;
	}
}

void	create_new_cmd(t_cmd *cmds, t_fullcmd **current)
{
	int			i;
	t_fullcmd	*arg_check;

	i = 0;
	cmds->cmd = gc_strdup((*current)->str);
	arg_check = (*current);
	while (arg_check && arg_check->is_cmd)
	{
		i++;
		arg_check = arg_check->next;
	}
	cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
	i = 0;
	while ((*current) && (*current)->is_cmd)
	{
		cmds->args[i] = gc_strdup((*current)->str);
		i++;
		(*current) = (*current)->next;
	}
	cmds->args[i] = NULL;
}

int	is_last(t_fullcmd **fullcmd)
{
	t_fullcmd	*current;

	current = *fullcmd;
	while (current)
	{
		if (current->type == PIPE)
			return (0);
		current = current->next;
	}
	return (1);
}

void	init_pipe(t_data *data, t_cmd *cmd, t_fullcmd **fullcmd,
			t_bool(is_first))
{
	if (is_first == false)
	{
		dup2(data->fd[0], cmd->fd_redir[0]);
		close(data->fd[0]);
		close(data->fd[1]);
	}
	if (is_last(fullcmd) == 0)
	{
		if (pipe(data->fd) == -1)
		{
			error_mess(NULL, NULL);
			return ;
		}
		dup2(data->fd[1], cmd->fd_redir[1]);
	}
}
