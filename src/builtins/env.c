/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:45:55 by neleon            #+#    #+#             */
/*   Updated: 2024/11/27 15:00:37 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_data *data)
{
	t_env	*curr;

	curr = data->envp_cpy;
	while (curr)
	{
		if (curr->value)
			printf("%s=%s\n", curr->key, curr->value);
		else if (curr->equal && !curr->value)
			printf("%s=\n", curr->key);
		curr = curr->next;
	}
  data->exit_status = 0;
}
