/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:46:13 by neleon            #+#    #+#             */
/*   Updated: 2024/11/25 15:46:20 by neleon           ###   ########.fr       */
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

static t_bool	check_args_count(t_data *data)
{
	if (data->cmds->args[1] && data->cmds->args[2])
	{
		printf("exit: too many arguments\n");
		data->exit_status = 1;
		return (true);
	}
	return (false);
}

static void	validate_status(t_data *data, int *status)
{
	if (!is_valid_num(data->cmds->args[1]))
	{
		printf("exit: %s : numeric argument required\n", data->cmds->args[1]);
		gc_mem(FULL_CLEAN, 0, NULL);
		exit(2);
	}
	*status = ft_atol(data->cmds->args[1]);
	if (*status > INT_MAX || *status < INT_MIN)
	{
		printf("exit: %s : numeric argument required\n", data->cmds->args[1]);
		gc_mem(FULL_CLEAN, 0, NULL);
		exit(2);
	}
}

void	ft_exit(t_data *data)
{
	int	status;

	status = 0;
	if (data->cmds->args[1])
		validate_status(data, &status);
	if (check_args_count(data))
		return ;
	if (data->cmds->args[1])
		ciao(status);
	ciao(data->exit_status);
}
