/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:21:16 by elilliu           #+#    #+#             */
/*   Updated: 2024/11/27 20:10:16 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_fd(char *operator, char *file)
{
	int	fd;

	fd = 0;
	if (ft_strncmp(operator, ">", 2) == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_APPEND | O_CREAT, 0644);
	return (fd);
}

void	redir_output(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (data->cmds->str[i])
	{
		if (ft_strncmp(data->cmds->str[i], ">", 2) == 0
			|| ft_strncmp(data->cmds->str[i], ">>", 3) == 0)
		{
			if (!data->cmds->str[i + 1])
				return ((void)error_mess(NULL, NULL));
			if (fd)
				close(fd);
			fd = new_fd(data->cmds->str[i], data->cmds->str[i + 1]);
			if (fd == -1)
				return ((void)error_mess(NULL, NULL));
		}
		i++;
	}
	if (fd && data->cmds->next)
		dup2(fd, data->fd[1]);
	else if (fd)
		dup2(fd, STDOUT_FILENO);
}
