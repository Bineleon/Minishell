/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:47 by neleon            #+#    #+#             */
/*   Updated: 2024/10/23 20:00:21 by bineleon         ###   ########.fr       */
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
  // t_env  *curr = data->envp_cpy;
  // while (curr->next)
  // {
  //     printf("key = %s   value = %s\n", curr->key, curr->value);
  //     curr = curr->next;
  // }
	while (1)
	{
		ft_prompt(data);
		// ft_print_lst(cmd_arg);
	}
	return (0);
}
