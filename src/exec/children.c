/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/12 16:28:35 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_child(t_data *data)
{
	data->open_process = true;
	// signal_open_process();
	redir_input(data);
	if (redir_output(data, data->cmds) == 0)
	{
		if (data->cmds->next)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			close(data->fd[1]);
			close(data->fd[0]);
		}
	}
	if (data->fd[2] != -1)
		close(data->fd[2]);
	if (data->fd[1] != -1)
		close(data->fd[0]);
	if (data->fd[0] != -1)
		close(data->fd[1]);
	exec_cmd(data);
}

void	middle_child(t_data *data)
{
	data->open_process = true;
	// signal_open_process();
	if (redir_input(data) == 0)
		dup2(data->fd[2], STDIN_FILENO);
	if (redir_output(data, data->cmds) == 0)
		dup2(data->fd[1], STDOUT_FILENO);
	close(data->fd[2]);
	close(data->fd[1]);
	close(data->fd[0]);
	exec_cmd(data);
}

void	last_child(t_data *data)
{
	data->open_process = true;
	// signal_open_process();
	if (redir_input(data) == 0)
		dup2(data->fd[2], STDIN_FILENO);
	close(data->fd[2]);
	close(data->fd[1]);
	close(data->fd[0]);
	redir_output(data, data->cmds);
	exec_cmd(data);
}
