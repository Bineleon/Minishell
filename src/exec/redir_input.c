/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:20:10 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/23 14:53:06 by elilliu@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_input(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (data->cmds->str[i])
	{
		if (ft_strncmp(data->cmds->str[i], "<", 1) == 0)
		{
			if (!data->cmds->str[i + 1])
				return ((void)error_mess(NULL, NULL));
			if (fd)
				close(fd);
			fd = open(data->cmds->str[i + 1], O_RDONLY);
			if (fd == -1)
				return ((void)error_mess(NULL, NULL));
		}
		i++;
	}
	if (fd && data->cmds->prev)
		dup2(fd, data->fd[0]);
	else if (fd)
		dup2(fd, STDIN_FILENO);
}
