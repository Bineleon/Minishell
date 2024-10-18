/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:39:12 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/18 21:27:07 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	which_child(t_data *data)
{
	if (!data->cmd->prev)
		first_child(data);
	else if (!data->cmd->next)
		last_child(data);
	else
		middle_child(data);
	if (data->cmd->next)
	{
		dup2(data->fd[1], STDOUT_FILENO);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
	}
}

void	exec(t_data *data)
{
	while (data->cmds != NULL)
	{
		if (data->cmd->next)
		{
			if (pipe(data->fd) == -1)
				return ((void)error_mess(NULL, NULL));
		}
		data->pid = fork();
		if (data->pid == -1)
			return (error_mess(NULL, NULL), 0);
		if (data->pid == 0)
			which_child(data);
		if (data->cmd->next)
		{
			dup2(data->fd[0], STDIN_FILENO);
			close(data->fd[0]);
			close(data->fd[1]);
		}
		data->cmds = data->cmds->next;
	}
	while (wait(NULL) != -1)
		continue ;
}
