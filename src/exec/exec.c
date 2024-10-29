/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:39:12 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/29 23:50:36 by neleon           ###   ########.fr       */
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

// void	exec(t_data *data)
// {
// 	int i = 0;
// 	printf("bienvenue dans l'exec!\n");
// 	printf("JE SUIS DANS EXEC PREMIER TOKEN = %s\n", data->token_fullcmd->str);
// 	init_cmds(data);
// 	printf("JE SUIS DANS EXEC PREMIERE CMD = %s\n", data->cmds->str[0]);
// 	while (data->cmds != NULL)
// 	{
// 		printf("-----%s\n", data->cmds->str[i]);
// 		i++;
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
// 		if (data->cmds->next)
// 		{
// 			dup2(data->fd[0], STDIN_FILENO);
// 			close(data->fd[0]);
// 			close(data->fd[1]);
// 		}
// 		data->cmds = data->cmds->next;
// 	}
// 	while (wait(NULL) != -1)
// 		continue ;
// }


void	exec(t_data *data)
{
	int i = 0;
	t_cmd *tmp;

	// printf("bienvenue dans l'exec!\n");
	// printf("JE SUIS DANS EXEC PREMIER TOKEN = %s\n", data->token_fullcmd->str);
	init_cmds(data);
	tmp = data->cmds;
	// printf("JE SUIS DANS EXEC PREMIERE CMD = %s\n", data->cmds->str[0]);
	while (tmp != NULL)
	{
		// printf("-----%s\n", tmp->str[i]);
		i++;
		if (tmp->next)
		{
			if (pipe(data->fd) == -1)
				return ((void)error_mess(NULL, NULL));
		}
		data->pid = fork();
		if (data->pid == -1)
			return ((void)error_mess(NULL, NULL));
		if (data->pid == 0)
			which_child(data);
		if (tmp->next)
		{
			dup2(data->fd[0], STDIN_FILENO);
			close(data->fd[0]);
			close(data->fd[1]);
		}
		tmp = tmp->next;
	}
	while (wait(NULL) != -1)
		continue ;
}