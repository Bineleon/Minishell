/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:47 by neleon            #+#    #+#             */
/*   Updated: 2024/09/12 15:56:05 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
  (void)envp;
  t_lst *cmd_arg;

  cmd_arg = ft_lstnew(NULL);
	while(1)
	{
		ft_prompt(&cmd_arg);
    ft_print_lst(cmd_arg);
	}
	return (0);
}
