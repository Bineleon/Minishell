/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:07:41 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/10/25 19:20:13 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_cmd(t_data *data, t_fullcmd *fullcmd)
{
	int	i;

	i = 0;
	while (data->cmds)
		data->cmds = data->cmds->next;
	while (fullcmd->str && fullcmd->type != PIPE && fullcmd->type != IN
		&& fullcmd->type != OUT)
	{
		if (i == 0)
			data->cmds->cmd = gc_strdup(fullcmd->str);
		data->cmds->args[i] = gc_strdup(fullcmd->str);
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
	while (data->token_fullcmd->str)
	{
		new_cmd(data, &data->token_fullcmd);
		while (data->token_fullcmd && data->token_fullcmd->type != PIPE)
			data->token_fullcmd = data->token_fullcmd->next;
		if (data->token_fullcmd && data->token_fullcmd->type == PIPE)
			data->token_fullcmd = data->token_fullcmd->next;
	}
}
