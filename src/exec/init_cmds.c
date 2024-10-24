/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:07:41 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/10/24 14:30:16 by elilliu@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_cmd(t_data *data, t_fullcmd *fullcmd)
{
	while (data->cmds)
		data->cmds = data->cmds->next;
	while (fullcmd->str && ft_strncmp(''))
}

void	init_cmds(t_data *data)
{
	int	i;

	i = 0;
	data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
	
}
