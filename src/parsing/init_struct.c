/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:14:19 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/27 18:11:39 by bineleon         ###   ########.fr       */
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
    data->envp_cpy = cpy_envp(envp);
    data->garbage = NULL;
}
