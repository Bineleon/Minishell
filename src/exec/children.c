/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/13 18:34:52 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fullclose_fd(t_data *data, int a, int b, int c)
{
	if (a >= 0 && data->fd[a] != -1)
		close(data->fd[a]);
	if (b >= 0 && data->fd[b] != -1)
		close(data->fd[b]);
	if (c >= 0 && data->fd[c] != -1)
		close(data->fd[c]);
}

void	first_child(t_data *data)
{
	int	i;

	data->open_process = true;
	if (redir_input(data) == 2)
	{
		fullclose_fd(data, 0, 1, 2);
		gc_mem(FULL_CLEAN, 0, NULL);
		exit(data->exit_status);
	}
	i = redir_output(data, data->cmds);
	if (i == 0)
	{
		if (data->cmds->next)
		{
			dup2(data->fd[1], STDOUT_FILENO);
			fullclose_fd(data, 1, -1, -1);
		}
	}
	else if (i == 2)
	{
		fullclose_fd(data, 0, 1, 2);
		gc_mem(FULL_CLEAN, 0, NULL);
		exit(data->exit_status);
	}
	fullclose_fd(data, 0, 1, 2);
	exec_cmd(data);
}

void	middle_child(t_data *data)
{
	int	i;
	int	j;

	data->open_process = true;
	j = redir_input(data);
	if (j == 0)
		dup2(data->fd[2], STDIN_FILENO);
	else if (j == 2)
	{
		fullclose_fd(data, 0, 1, 2);
		gc_mem(FULL_CLEAN, 0, NULL);
		exit(data->exit_status);
	}
	i = redir_output(data, data->cmds);
	if (i == 0)
		dup2(data->fd[1], STDOUT_FILENO);
	else if (i == 2)
	{
		fullclose_fd(data, 0, 1, 2);
		gc_mem(FULL_CLEAN, 0, NULL);
		exit(data->exit_status);
	}
	fullclose_fd(data, 0, 1, 2);
	exec_cmd(data);
}

void	last_child(t_data *data)
{
	int	j;

	data->open_process = true;
	j = redir_input(data);
	if (j == 0)
  {
		dup2(data->fd[2], STDIN_FILENO);
  }
	else if (j == 2)
	{
		fullclose_fd(data, 0, 1, 2);
		gc_mem(FULL_CLEAN, 0, NULL);
		exit(data->exit_status);
	}
	fullclose_fd(data, 0, 1, 2);
	if (redir_output(data, data->cmds) == 2)
	{
		fullclose_fd(data, 0, 1, 2);
		gc_mem(FULL_CLEAN, 0, NULL);
		exit(data->exit_status);
	}
	exec_cmd(data);
}
