/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/14 16:44:55 by bineleon         ###   ########.fr       */
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

static void	exit_child(t_data *data, int a, int b, int c)
{
	fullclose_fd(data, a, b, c);
	gc_mem(FULL_CLEAN, 0, NULL);
	exit(data->exit_status);
}

void	config_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	first_child(t_data *data)
{
	int	i;

	data->open_process = false;
  config_child_signals();
	if (redir_input(data) == 2)
		exit_child(data, 0, 1, 2);
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
		exit_child(data, 0, 1, 2);
	fullclose_fd(data, 0, 1, 2);
	exec_cmd(data);
}

void	middle_child(t_data *data)
{
	int	i;
	int	j;

	data->open_process = false;
  config_child_signals();
	j = redir_input(data);
	if (j == 0)
		dup2(data->fd[2], STDIN_FILENO);
	else if (j == 2)
		exit_child(data, 0, 1, 2);
	i = redir_output(data, data->cmds);
	if (i == 0)
		dup2(data->fd[1], STDOUT_FILENO);
	else if (i == 2)
		exit_child(data, 0, 1, 2);
	fullclose_fd(data, 0, 1, 2);
	exec_cmd(data);
}

void	last_child(t_data *data)
{
	int	j;

	data->open_process = false;
  config_child_signals();
	j = redir_input(data);
	if (j == 0)
		dup2(data->fd[2], STDIN_FILENO);
	else if (j == 2)
		exit_child(data, 0, 1, 2);
	fullclose_fd(data, 0, 1, 2);
	if (redir_output(data, data->cmds) == 2)
		exit_child(data, 0, 1, 2);
	exec_cmd(data);
}
