/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:09:28 by neleon            #+#    #+#             */
/*   Updated: 2024/11/27 19:43:43 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_option(char **args)
{
	if (ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0)
		return (true);
	return (false);
}

void	ft_echo(t_cmd *cmds)
{
	t_bool	nl_option;
	int		i;
  t_data *data;

	i = 1;
  data = get_data();
	nl_option = check_option(cmds->args);
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
