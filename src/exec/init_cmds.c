/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:07:41 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/10/25 20:39:15 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_cmd(t_data *data, t_fullcmd *fullcmd)
{
	int		i;

	i = 0;
	printf("\n\nICI\n\n");
	while (fullcmd->str && fullcmd->type != PIPE && fullcmd->type != IN
		&& fullcmd->type != OUT)
	{
		printf("\n\nstr: %s\n", data->cmds->args[i]);
		if (i == 0)
			data->cmds->cmd = gc_strdup(fullcmd->str);
		data->cmds->args[i] = gc_strdup(fullcmd->str);
		printf("\n\nICI\n\n");
		data->cmds->str[i] = gc_strdup(fullcmd->str);
		i++;
		fullcmd = fullcmd->next;
	}
	while (fullcmd->str && fullcmd->type != PIPE)
	{
		data->cmds->str[i] = gc_strdup(fullcmd->str);
		i++;
		fullcmd = fullcmd->next;
	}
}

void	init_cmds(t_data *data)
{
	int	i;

	i = 0;
	data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
	init_cmd(data->cmds);

	new_cmd(data, data->token_fullcmd);
	while (data->token_fullcmd->str)
	{
		while(data->cmds)
		{
			data->cmds->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
			data->cmds->next->prev = data->cmds;
			data->cmds = data->cmds->next;
		}
		init_cmd(data->cmds);
		new_cmd(data, data->token_fullcmd);
		while (data->token_fullcmd && data->token_fullcmd->type != PIPE)
			data->token_fullcmd = data->token_fullcmd->next;
		if (data->token_fullcmd && data->token_fullcmd->type == PIPE)
			data->token_fullcmd = data->token_fullcmd->next;
		data->token_fullcmd = data->token_fullcmd->next;
	}
}
