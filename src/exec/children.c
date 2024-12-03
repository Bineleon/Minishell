/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:17:55 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/03 22:46:00 by elilliu@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_child(t_data *data)
{
	redir_input(data);
	heredoc(data);
	if (data->cmds->next)
	{
		dup2(data->fd[1], STDOUT_FILENO);
		if (data->fd[2] != -1)
			close(data->fd[2]);
		close(data->fd[1]);
		close(data->fd[0]);
	}
	redir_output(data);
	exec_cmd(data);
}

void	middle_child(t_data *data)
{
	dup2(data->fd[2], STDIN_FILENO);
	redir_input(data);
	heredoc(data);
	dup2(data->fd[1], STDOUT_FILENO);
	redir_output(data);
	close(data->fd[2]);
	close(data->fd[1]);
	close(data->fd[0]);
	exec_cmd(data);
}

void	last_child(t_data *data)
{
	dup2(data->fd[2], STDIN_FILENO);
	redir_input(data);
	heredoc(data);
	redir_output(data);
	close(data->fd[2]);
	close(data->fd[1]);
	close(data->fd[0]);
	exec_cmd(data);
}
