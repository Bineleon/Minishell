/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:09:28 by neleon            #+#    #+#             */
/*   Updated: 2024/12/05 17:31:14 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_option(char *arg)
{
	if (ft_strcmp(arg, "-n") == 0)
		return (true);
	return (false);
}

t_bool check_other_opt(char *arg)
{
  if (arg[0] == '-' && arg[1] != 'n')
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
	while (cmds->args[i])
	{
    nl_option = check_option(cmds->args[i]);
    while (check_option(cmds->args[i]))
      i++;
		printf("%s", cmds->args[i]);
		if (cmds->args[i + 1])
			printf(" ");
		i++;
	}
	if (!nl_option)
		printf("\n");
	data->exit_status = 0;
}
