/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:14:19 by bineleon          #+#    #+#             */
/*   Updated: 2024/10/29 19:05:36 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*get_data(void)
{
	static t_data	data;

	return (&data);
}

void	init_data(t_data *data, char **envp)
{
	data->cmds = NULL;
	data->token_fullcmd = NULL;
	data->garbage = NULL;
	data->cmds_count = 0;
	data->exit_status = 0;
	data->envp_cpy = env_cpy(envp);
}

void	init_env(t_env *env)
{
	env->key = NULL;
	env->value = NULL;
	env->next = NULL;
}

void	init_cmd(t_cmd *cmd)
{
	cmd->str = NULL;
	cmd->next = NULL;
	cmd->args = NULL;
	cmd->cmd = NULL;
	cmd->prev = NULL;
}
