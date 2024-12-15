/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:46:13 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 15:44:47 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_bool	is_valid_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static t_bool	check_args_count(t_cmd *cmds)
{
	t_data	*data;

	data = get_data();
	if (cmds->args[1] && cmds->args[2])
	{
		error_mess("exit", "too many arguments\n");
		data->exit_status = 1;
		return (true);
	}
	return (false);
}

static void	validate_status(t_cmd *cmds, int *status)
{
	if (!is_valid_num(cmds->args[1]))
	{
		error_mess("exit", cmds->args[1]);
		ft_putstr_fd(" : numeric argument required\n", 2);
		gc_mem(FULL_CLEAN, 0, NULL);
		gc_mem_env(FULL_CLEAN, 0, NULL);
		exit(2);
	}
	*status = ft_atol(cmds->args[1]);
	if (*status > INT_MAX || *status < INT_MIN)
	{
		error_mess("exit", cmds->args[1]);
		ft_putstr_fd(" : numeric argument required\n", 2);
		gc_mem(FULL_CLEAN, 0, NULL);
		gc_mem_env(FULL_CLEAN, 0, NULL);
		exit(2);
	}
}

void	ft_exit(t_cmd *cmds)
{
	int		status;
	t_data	*data;

	data = get_data();
	status = 0;
  ft_putstr_fd("exit\n", data->fd_);
	if (cmds->args[1])
		validate_status(cmds, &status);
	if (check_args_count(cmds))
		return ;
	if (cmds->args[1])
		ciao(status);
	ciao(data->exit_status);
}
