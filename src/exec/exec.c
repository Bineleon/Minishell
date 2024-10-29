/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:39:12 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/29 11:48:33 by elilliu          ###   ########.fr       */
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
	if (data->cmds->next)
	{
		dup2(data->fd[1], STDOUT_FILENO);
		close(data->fd[0]);
		close(data->fd[1]);
	}
}

void	exec(t_data *data)
{
	init_cmds(data);
	while (data->cmds != NULL)
	{
		if (data->cmds->next)
		{
			if (pipe(data->fd) == -1)
				return ((void)error_mess(NULL, NULL));
		}
		data->pid = fork();
		if (data->pid == -1)
			return ((void)error_mess(NULL, NULL));
		if (data->pid == 0)
			which_child(data);
		if (data->cmds->next)
		{
			dup2(data->fd[0], STDIN_FILENO);
			close(data->fd[0]);
			close(data->fd[1]);
		}
		data->cmds = data->cmds->next;
	}
	while (wait(NULL) != -1)
		continue ;
}
