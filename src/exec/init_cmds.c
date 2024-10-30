/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:07:41 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/10/30 17:41:09 by elilliu@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_str(t_cmd *cmds, t_fullcmd **fullcmd)
{
	int			i;
	t_fullcmd	*firstcmd;

	i = 0;
	firstcmd = *fullcmd;
	while (cmds->args[i])
		i++;
	while (*fullcmd && (*fullcmd)->type != PIPE)
	{
		i++;
		*fullcmd = (*fullcmd)->next;
	}
	cmds->str = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
	i = 0;
	cmds->str[i] = gc_strdup(cmds->args[i]);
	while (cmds->args[++i])
		cmds->str[i] = gc_strdup(cmds->args[i]);
	*fullcmd = firstcmd;
	while (*fullcmd && (*fullcmd)->type != PIPE)
	{
		cmds->str[i++] = gc_strdup((*fullcmd)->str);
		*fullcmd = (*fullcmd)->next;
	}
	cmds->str[i] = NULL;
}

void	new_cmd(t_cmd *cmds, t_fullcmd **fullcmd)
{
	int			i;
	t_fullcmd	*firstcmd;

	i = 0;
	firstcmd = *fullcmd;
	while (*fullcmd && (*fullcmd)->type != PIPE && (*fullcmd)->type != IN
		&& (*fullcmd)->type != OUT)
	{
		i++;
		*fullcmd = (*fullcmd)->next;
	}
	cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
	cmds->cmd = gc_strdup(firstcmd->str);
	i = 0;
	*fullcmd = firstcmd;
	while (*fullcmd && (*fullcmd)->type != PIPE && (*fullcmd)->type != IN
		&& (*fullcmd)->type != OUT)
	{
		cmds->args[i] = gc_strdup((*fullcmd)->str);
		i++;
		*fullcmd = (*fullcmd)->next;
	}
	cmds->args[i] = NULL;
}

void	init_cmds(t_data *data)
{
	t_cmd		*cmdstmp;
	t_fullcmd	*fullcmdtmp;

	data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
	init_cmd(data->cmds);
	cmdstmp = data->cmds;
	fullcmdtmp = data->token_fullcmd;
	while (fullcmdtmp)
	{
		new_cmd(cmdstmp, &fullcmdtmp);
		new_str(cmdstmp, &fullcmdtmp);
		if (fullcmdtmp && fullcmdtmp->type == PIPE)
		{
			fullcmdtmp = fullcmdtmp->next;
			cmdstmp->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
			cmdstmp->next->prev = cmdstmp;
			cmdstmp = cmdstmp->next;
			init_cmd(cmdstmp);
		}
	}
}
