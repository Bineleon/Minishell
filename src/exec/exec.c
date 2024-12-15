/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:23:04 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 23:22:10 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_child(t_data *data)
{
	t_cmd	*current;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	data->open_process = true;
	dup2(data->cmds->fd_redir[0], STDIN_FILENO);
	dup2(data->cmds->fd_redir[1], STDOUT_FILENO);
	current = data->cmds;
	while (current)
	{
		close(current->fd_redir[0]);
		close(current->fd_redir[1]);
		current = current->next;
	}
	exec_cmd(data);
}

int	just_builtin(t_data *data)
{
	if (is_builtin(data->cmds->cmd) && data->cmds->is_first
		&& data->cmds->next == NULL)
	{
		close(data->cmds->fd_redir[0]);
		close(data->cmds->fd_redir[1]);
		if (redir_builtins(data) == 0)
			return (1);
		exec_builtin(data, data->cmds);
		return (1);
	}
	return (0);
}

void	wait_pid(t_data *data)
{
	int	status;

	while (1)
	{
		data->pid = waitpid(-1, &status, 0);
		if (data->pid == -1)
			break ;
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
}

int	init_exec(t_data *data)
{
	data->sig = 0;
	if (!init_cmds(data))
		return (0);
	if (data->sig == 130)
		return (0);
	data->open_process = false;
	if (verif_interactive_mode(data) == 0)
		return (0);
	return (1);
}

void	exec(t_data *data)
{
	if (init_exec(data) == 0)
		return ;
	while (data->cmds != NULL)
	{
		if (redir_puts(data, data->cmds) == 0)
		{
			close(data->cmds->fd_redir[0]);
			close(data->cmds->fd_redir[1]);
			data->cmds = data->cmds->next;
			continue ;
		}
		if (just_builtin(data) == 1)
			return ;
		data->pid = fork();
		if (data->pid == -1)
			return (gc_mem(FULL_CLEAN, 0, NULL), (void)error_mess(NULL, NULL));
		if (data->pid == 0)
			exec_child(data);
		finish_process(data);
		data->cmds = data->cmds->next;
	}
	if (data->fd[2] != -1)
		close(data->fd[2]);
	wait_pid(data);
	data->open_process = false;
}
