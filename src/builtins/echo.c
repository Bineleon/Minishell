/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:09:28 by neleon            #+#    #+#             */
/*   Updated: 2024/12/07 17:21:24 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_option(char *arg)
{
	int i;

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

t_bool	check_other_opt(char *arg)
{
	if (arg[0] == '-' && arg[1] && arg[1] != 'n')
		return (true);
	return (false);
}
void	ft_echo(t_cmd *cmds)
{
	t_bool	nl_option;
	int		i;
	t_data	*data;

	i = 1;
	data = get_data();
	nl_option = false;
	while (cmds->args[i] && check_option(cmds->args[i]))
	{
		nl_option = true;
		i++;
	}
	while (cmds->args[i])
	{
		printf("%s", cmds->args[i]);
		if (cmds->args[i + 1])
			printf(" ");
		i++;
	}
	if (!nl_option)
		printf("\n");
	data->exit_status = 0;
}
