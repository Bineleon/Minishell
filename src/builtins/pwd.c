/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:23:34 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 20:23:37 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_data *data)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
	{
		ft_putstr_fd(buf, data->fd_);
		ft_putstr_fd("\n", data->fd_);
		if (data->fd_ > 1)
			close(data->fd_);
		data->exit_status = 0;
	}
	else
	{
		perror("getcwd(): ");
		data->exit_status = 1;
	}
}
