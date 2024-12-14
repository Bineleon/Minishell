/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:39:12 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/14 16:12:19 by bineleon         ###   ########.fr       */
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
  data->hd_active = true;
	if (check_minishell_cmd(data))
	{
		printf(RED);
		ft_putstr_fd("\033[1;31mminishell : \033[0m\n",2);
		ft_putstr_fd("\033[1;31minteractive mode not allowed 💩\033[0m\n",2);
		printf(RESET);
		data->exit_status = 127;
		return ;
	}
	while (data->cmds != NULL)
	{
    data->open_process = false;
    // data->hd_active = true;
		if (is_builtin(data->cmds->cmd) && data->cmds->is_first
			&& data->cmds->next == NULL)
		{
			if (redir_input(data) == 2)
          return;
			redir_builtins(data);
			exec_builtin(data, data->cmds);
      if (data->fd_ > 0)
				close(data->fd_);
			return ;
		}
		if (data->cmds->next)
		{
			if (pipe(data->fd) == -1)
      {
        gc_mem(FULL_CLEAN, 0, NULL);
				return ((void)error_mess(NULL, NULL));
      } // ADD FULL_CLEAN + close + exit
		}
		data->pid = fork();
    signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (data->pid == -1)
    {
      gc_mem(FULL_CLEAN, 0, NULL);
			return ((void)error_mess(NULL, NULL)); // add full clean
    }  signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (data->pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			which_child(data);
		}
    // data->hd_active = false;
    signal(SIGQUIT, handle_child_sigquit);
		data->open_process = true;
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
