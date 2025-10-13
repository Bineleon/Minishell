/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:24:51 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 17:25:04 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
