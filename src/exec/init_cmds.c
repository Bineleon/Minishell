/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:07:41 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/10/29 13:09:50 by elilliu          ###   ########.fr       */
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

	printf("fullcmd: %s\n\n", (*fullcmd)->str);
	i = 0;
	firstcmd = *fullcmd;
	while (*fullcmd && (*fullcmd)->type != PIPE && (*fullcmd)->type != IN
		&& (*fullcmd)->type != OUT)
	{
		i++;
		*fullcmd = (*fullcmd)->next;
	}
	printf("i: %d\n", i);
	cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
	cmds->cmd = gc_strdup(firstcmd->str);
	i = 0;
	*fullcmd = firstcmd;
	printf("fullcmd2: %s\n\n", (*fullcmd)->str);
	while (*fullcmd && (*fullcmd)->type != PIPE && (*fullcmd)->type != IN
		&& (*fullcmd)->type != OUT)
	{
		cmds->args[i] = gc_strdup((*fullcmd)->str);
		printf("strdup OK\n\n");
		i++;
		*fullcmd = (*fullcmd)->next;
	}
	printf("c tout bon\n\n");
	cmds->args[i] = NULL;
}

void	init_cmds(t_data *data)
{
	t_cmd		*cmdstmp;
	t_fullcmd	*fullcmdtmp;
	t_fullcmd	*test;

	test = data->token_fullcmd;
	while (test)
	{
		printf("token: %s\n\n", test->str);
		test = test->next;
	}
	data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
	init_cmd(data->cmds);
	cmdstmp = data->cmds;
	fullcmdtmp = data->token_fullcmd;
	while (fullcmdtmp)
	{
		printf ("\n\nICI\n\n");
		new_cmd(cmdstmp, &fullcmdtmp);
		printf("fullcmdtmp: %s\n", fullcmdtmp->str);
		new_str(cmdstmp, &fullcmdtmp);
		if (fullcmdtmp && fullcmdtmp->type == PIPE)
		{
			printf("normalement on rentre pas la dedans\n\n");
			fullcmdtmp = fullcmdtmp->next;
			cmdstmp->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
			cmdstmp->next->prev = cmdstmp;
			cmdstmp = cmdstmp->next;
			init_cmd(cmdstmp);
		}
	}
}
