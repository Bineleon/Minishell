/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:26:55 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/15 17:57:49 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*joinequal(char *key, char *value)
{
	char	*tmp;
	char	*str;

	tmp = gc_strjoin(key, "=");
	str = gc_strjoin(tmp, value);
	if (!str)
		return (gc_mem(FREE, 0, tmp), NULL);
	gc_mem(FREE, 0, tmp);
	return (str);
}

char	*join(char *path, char *cmd)
{
	char	*tmp;
	char	*str;

	tmp = gc_strjoin(path, "/");
	str = gc_strjoin(tmp, cmd);
	if (!str)
		return (gc_mem(FREE, 0, tmp), (NULL));
	gc_mem(FREE, 0, tmp);
	return (str);
}

void	init_data_fd(t_data *data)
{
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->fd[2] = -1;
}

int	redir_puts(t_data *data, t_cmd *cmdstmp)
{
	if (redir_input(data, cmdstmp) == 130)
		return (0);
	redir_output(data, cmdstmp);
	return (1);
}
