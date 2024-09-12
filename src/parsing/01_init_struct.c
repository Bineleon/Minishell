/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:27:53 by neleon            #+#    #+#             */
/*   Updated: 2024/09/12 19:41:43 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_data	*init_and_alloc_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	data->envp_cpy = cpy_envp(envp);
	return (data);
}