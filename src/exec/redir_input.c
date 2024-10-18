/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:20:10 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/18 21:21:08 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_input(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (data->cmd->str[i])
	{
		if (ft_strncmp(data->cmd->str[i], "<") == 0)
		{
			if (!data->cmd->str[i + 1])
				return ((void)error_mess(NULL, NULL));
			if (fd)
				close(fd);
			fd = open(data->cmd->str[i + 1], O_RDONLY);
			if (fd == -1)
				return ((void)error_mess(NULL, NULL));
		}
		i++;
	}
	if (fd && data->cmd->prev)
		dup2(fd, data->fd[0]);
	else if (fd)
		dup2(fd, STDIN_FILENO);
}
