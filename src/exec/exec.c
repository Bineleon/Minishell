/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelbi <neleon@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:39:12 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/09 11:58:40 by nelbi            ###   ########.fr       */
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


void exec(t_data *data)
{
    int status;

    init_cmds(data);
    data->open_process = false;
    while (data->cmds != NULL)
    {
        if (is_builtin(data->cmds->cmd) && !data->cmds->prev && !data->cmds->next)
        {
            exec_builtin(data, data->cmds);
            return;
        }
        if (data->cmds->next)
        {
            if (pipe(data->fd) == -1)
                return ((void)error_mess(NULL, NULL));
        }
        data->pid = fork();
        if (data->pid == -1)
            return ((void)error_mess(NULL, NULL));
        if (data->pid == 0)
        {
            data->open_process = true;
            which_child(data);
        }
        data->open_process = true;
        if (data->fd[2] != -1)
            close(data->fd[2]);
        data->fd[2] = data->fd[0];
        close(data->fd[1]);
        data->cmds = data->cmds->next;
    }
    if (data->fd[2] != -1)
        close(data->fd[2]);
    // while (wait(NULL) != -1)
    //     continue;
    while (1)
    {
        data->pid = waitpid(-1, &status, 0);
        if (data->pid == -1)
            break;
        if (WIFEXITED(status))
            data->exit_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            data->exit_status = 128 + WTERMSIG(status);
    }
    data->open_process = false;
}


// void	exec(t_data *data)
// {
// 	init_cmds(data);
// 	while (data->cmds != NULL)
// 	{
// 		if (is_builtin(data->cmds->cmd) && !data->cmds->prev
// 			&& !data->cmds->next)
// 		{
// 			exec_builtin(data, data->cmds);
// 			return ;
// 		}
// 		if (data->cmds->next)
// 		{
// 			if (pipe(data->fd) == -1)
// 				return ((void)error_mess(NULL, NULL));
// 		}
// 		data->pid = fork();
// 		if (data->pid == -1)
// 			return ((void)error_mess(NULL, NULL));
// 		if (data->pid == 0)
// 			which_child(data);
// 		if (data->fd[2] != -1)
// 			close(data->fd[2]);
// 		data->fd[2] = data->fd[0];
// 		close(data->fd[1]);
// 		data->cmds = data->cmds->next;
// 	}
// 	if (data->fd[2] != -1)
// 		close(data->fd[2]);
// 	while (wait(NULL) != -1)
// 		continue ;
// }
