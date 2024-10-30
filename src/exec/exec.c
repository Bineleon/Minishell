/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/10/30 22:29:13 by neleon           ###   ########.fr       */
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
			// dup2(data->fd[0], STDIN_FILENO); !!! Pas de dup2 dans le main, seulement dans les children
			// close(data->fd[0]);
			// close(data->fd[1]);
		}
		data->cmds = data->cmds->next;
	}
	while (wait(NULL) != -1)
		continue ;
}