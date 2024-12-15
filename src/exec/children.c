/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/15 13:56:10 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void	fullclose_fd(t_data *data, int a, int b, int c)
// {
// 	if (a >= 0 && data->fd[a] != -1)
// 		close(data->fd[a]);
// 	if (b >= 0 && data->fd[b] != -1)
// 		close(data->fd[b]);
// 	if (c >= 0 && data->fd[c] != -1)
// 		close(data->fd[c]);
// }

void	config_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	first_child(t_data *data)
{
	data->open_process = true;
	config_child_signals();
	dup2(data->cmds->fd_redir[0], STDIN_FILENO);
	dup2(data->cmds->fd_redir[1], STDOUT_FILENO);
	close(data->cmds->fd_redir[0]);
	close(data->cmds->fd_redir[1]);
	exec_cmd(data);
}

void	middle_child(t_data *data)
{
	data->open_process = true;
	config_child_signals();
	dup2(data->cmds->fd_redir[0], STDIN_FILENO);
	dup2(data->cmds->fd_redir[1], STDOUT_FILENO);
	close(data->cmds->fd_redir[0]);
	close(data->cmds->fd_redir[1]);
	exec_cmd(data);
}

void	last_child(t_data *data)
{
	data->open_process = true;
	config_child_signals();
	dup2(data->cmds->fd_redir[0], STDIN_FILENO);
	dup2(data->cmds->fd_redir[1], STDOUT_FILENO);
	close(data->cmds->fd_redir[0]);
	close(data->cmds->fd_redir[1]);
	exec_cmd(data);
}
