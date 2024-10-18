/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:21:16 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/18 21:21:50 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_output(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (data->cmd->str[i])
	{
		if (ft_strncmp(data->cmd->str[i], ">") == 0)
		{
			if (!data->cmd->str[i + 1])
				return ((void)error_mess(NULL, NULL));
			if (fd)
				close(fd);
			fd = open(data->cmd->str[i + 1], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
			if (fd == -1)
				return ((void)error_mess(NULL, NULL));
		}
		i++;
	}
	if (fd && data->cmd->next)
		dup2(fd, data->fd[1]);
	else if (fd)
		dup2(fd, STDOUT_FILENO);
}
