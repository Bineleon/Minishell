/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:47 by neleon            #+#    #+#             */
/*   Updated: 2024/09/26 17:32:06 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;
	// int		i;

	// i = 0;
	(void)ac;
	(void)av;

  data = get_data();
  init_data(data, envp);
	while (1)
	{
		ft_prompt(data);

		// ft_print_lst(cmd_arg);
	}
	return (0);
}
