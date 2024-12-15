/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:48:00 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 20:32:24 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_option(char *arg)
{
	int	i;

	i = 1;
	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (false);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

void	handle_echo_args(t_cmd *cmds, int *i, t_bool *nl_option)
{
	*nl_option = false;
	while (cmds->args[*i] && check_option(cmds->args[*i]))
	{
		*nl_option = true;
		(*i)++;
	}
}

void	handle_option(t_cmd *cmds, t_bool *nl_option, int *i)
{
	while (cmds->args[*i] && check_option(cmds->args[*i]))
	{
		*nl_option = true;
		(*i)++;
	}
}

static void	sub_echo(t_data *data, int fd, t_bool nl_option)
{
	if (!nl_option)
		ft_putstr_fd("\n", fd);
	data->exit_status = 0;
	if (fd > 1)
		close(fd);
}

void	ft_echo(t_cmd *cmds, int fd)
{
	t_bool	nl_option;
	int		i;
	t_data	*data;

	i = 1;
	data = get_data();
	nl_option = false;
	if (fd < 0)
		fd = 1;
	handle_option(cmds, &nl_option, &i);
	while (cmds->args[i])
	{
		if (ft_putstr_fd(cmds->args[i], fd) == -1)
		{
			perror("echo");
			data->exit_status = 1;
			return ;
		}
		if (cmds->args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	sub_echo(data, fd, nl_option);
}
