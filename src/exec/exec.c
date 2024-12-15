/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:39:12 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/15 02:11:20 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	which_child(t_data *data)
{
	if (!data->cmds->prev)
		first_child(data);
	else if (!data->cmds->next)
		last_child(data);
	else
		middle_child(data);
}

t_bool	check_minishell(char *cmd)
{
	if (cmd && (ft_strcmp(cmd, "./minishell") == 0 || ft_strcmp(cmd,
				"minishell") == 0))
		return (true);
	return (false);
}

t_bool	check_minishell_cmd(t_data *data)
{
	t_cmd	*current;

	current = data->cmds;
	if (current->cmd && current->next)
	{
		if (check_minishell(current->cmd))
			return (true);
	}
	current = current->next;
	while (current)
	{
		if (check_minishell(current->cmd))
			return (true);
		current = current->next;
	}
	return (false);
}

void	exec(t_data *data)
{
	int	status;

	init_cmds(data);
	data->open_process = false;
	if (check_minishell_cmd(data))
	{
		printf(RED);
		ft_putstr_fd("\033[1;31mminishell : interactive mode not allowed 💩\033[0m\n",
			2);
		printf(RESET);
		data->exit_status = 127;
		return ;
	}
	while (data->cmds != NULL)
	{
		data->open_process = false;
		if (is_builtin(data->cmds->cmd) && data->cmds->is_first
			&& data->cmds->next == NULL)
		{
			// redir_input(data);
			// redir_builtins(data);
			exec_builtin(data, data->cmds);
			return ;
		}
		// if (data->cmds->next)
		// {
		// 	if (pipe(data->fd) == -1) // ADD FULL_CLEAN + close + exit
		// 		return ((void)error_mess(NULL, NULL));
		// }
		data->pid = fork();
		if (data->pid == -1)
			return ((void)error_mess(NULL, NULL)); // add full clean
		if (data->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			handle_signals();
			which_child(data);
		}
		data->open_process = true;
		handle_signals();
		if (data->cmds->next)
			close(data->fd[1]);
		if (data->fd[2] != -1)
			close(data->fd[2]);
		data->fd[2] = data->fd[0];
		data->cmds = data->cmds->next;
	}
	if (data->fd[2] != -1)
		close(data->fd[2]);
	while (1)
	{
		data->pid = waitpid(-1, &status, 0);
		if (data->pid == -1)
			break ;
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
	}
	data->open_process = false;
}
