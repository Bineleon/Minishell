/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:47 by neleon            #+#    #+#             */
/*   Updated: 2024/09/19 19:19:49 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_lst	*cmd_arg;
	t_data	*data;
	int		i;

	i = 0;
	(void)ac;
	(void)av;
	(void)envp;
	cmd_arg = ft_lstnew(NULL);
	data = init_and_alloc_data(envp);
	while (1)
	{
		ft_prompt(&cmd_arg);

		// ft_print_lst(cmd_arg);
	}
	return (0);
}
