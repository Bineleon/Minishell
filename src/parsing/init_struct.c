/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:14:19 by bineleon          #+#    #+#             */
/*   Updated: 2024/10/23 14:41:59 by elilliu@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data *get_data(void)
{
      static t_data  data;
      return (&data);
}

void  init_data(t_data *data, char **envp)
{
    data->cmds = NULL;
    data->token_fullcmd = NULL;
    data->cmds_count = 0;
    data->envp_cpy = env_cpy(envp);
    data->garbage = NULL;
}

void init_env(t_env *env)
{
    env->key = NULL;
    env->value = NULL;
    env->next = NULL;
}
