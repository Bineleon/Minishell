/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:17:55 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/23 14:49:53 by elilliu@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	first_child(t_data *data)
{
	redir_input(data);
	if (data->cmds->next)
	{
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
	}
	redir_output(data);
	exec_cmd(data);
}

void	middle_child(t_data *data)
{
	redir_input(data);
	dup2(data->fd[1], STDOUT_FILENO);
	redir_output(data);
	close(data->fd[0]);
	close(data->fd[1]);
	exec_cmd(data);
}

void	last_child(t_data *data)
{
	redir_input(data);
	redir_output(data);
	close(data->fd[0]);
	close(data->fd[1]);
	exec_cmd(data);
}
