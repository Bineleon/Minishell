/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:17:55 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/30 22:30:53 by neleon           ###   ########.fr       */
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
	if (dup2(data->fd[0], STDIN_FILENO) == -1)
		printf("zizi\n");
	close(data->fd[0]);
	close(data->fd[1]);
	exec_cmd(data);
}
