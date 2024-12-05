/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:17:55 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/05 17:21:01 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_child(t_data *data)
{
	redir_input(data);
	heredoc(data);
  // if (is_builtin(data->cmds->args[0]))
  // {
  //   exec_builtin(data, data->cmds);  // Exécuter le builtin
  //   exit(data->exit_status);  // Terminer le processus
  // }
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
