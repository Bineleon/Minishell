/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:09:28 by neleon            #+#    #+#             */
/*   Updated: 2024/11/25 15:45:44 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_option(char **args)
{
	if (ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0)
		return (true);
	return (false);
}

void	ft_echo(t_data *data)
{
	t_bool	nl_option;
	int		i;

	i = 1;
	nl_option = check_option(data->cmds->args);
	while (data->cmds->args[i])
	{
		printf("%s", data->cmds->args[i]);
		if (data->cmds->args[i + 1])
			printf(" ");
		i++;
	}
	if (!nl_option)
		printf("\n");
	data->exit_status = 0;
}
