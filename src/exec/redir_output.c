/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/15 00:35:31 by elilliu@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_output_fd(t_data *data, t_redir *current_redir, int *fd)
{
	if (current_redir->type == OUT)
		(*fd) = open(current_redir->file_name,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (current_redir->type == APPEND)
		(*fd) = open(current_redir->file_name,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*fd == -1)
	{
		error_mess(current_redir->file_name, NULL);
		data->exit_status = 1;
		return (0);
	}
	return (1);
}

void	close_fd(int *fd)
{
	close(*fd);
	(*fd) = -1;
}

void	redir_builtins(t_data *data)
{
	t_redir	*current_redir;
	int		fd;

	if (!data->cmds || !data->cmds->redir)
	{
		data->fd_ = 0;
		return ;
	}
	current_redir = data->cmds->redir;
	fd = 0;
	while (current_redir)
	{
		if (current_redir->type == OUT || current_redir->type == APPEND)
		{
			if (fd > 0)
				close_fd(&fd);
			if (new_output_fd(data, current_redir, &fd) == 0)
				return ;
		}
		current_redir = current_redir->next;
	}
	if (fd > 0)
		data->fd_ = fd;
}

int	redir_cmd(t_data *data, t_cmd *cmd)
{
	t_redir	*current_redir;
	int		fd;

	if (!cmd || !cmd->redir)
		return (0);
	current_redir = cmd->redir;
	fd = -1;
	while (current_redir)
	{
		if (current_redir->type == OUT || current_redir->type == APPEND)
		{
			if (fd > 0)
			{
				close(fd);
				fd = -1;
			}
			if (new_output_fd(data, current_redir, &fd) == 0)
				return (1);
		}
		current_redir = current_redir->next;
	}
	if (fd > 0)
		dup2(fd, cmd->fd_redir[1]);
	return (0);
}

int	redir_output(t_data *data, t_cmd *cmd)
{
	if (!cmd || !cmd->redir)
		return (0);
	if (!is_builtin(cmd->cmd))
		return (redir_cmd(data, cmd));
	else
		return (0);
}
