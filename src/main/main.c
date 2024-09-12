/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:47 by neleon            #+#    #+#             */
/*   Updated: 2024/09/12 14:55:28 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
  (void)envp;
	while(1)
	{
		ft_prompt();
	}
	return (0);
}
