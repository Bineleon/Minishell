/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:47 by neleon            #+#    #+#             */
/*   Updated: 2024/12/06 14:10:11 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

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
	// while (1)
	// {
	handle_signals();
	ft_prompt(data);
	// }
	return (0);
}
