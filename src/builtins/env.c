/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:56:23 by neleon            #+#    #+#             */
/*   Updated: 2024/11/20 16:52:29 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_env *env_cpy)
{
	t_env	*curr;

	curr = env_cpy;
	while (curr)
	{
      if (curr->value)
        printf("%s=%s\n", curr->key, curr->value);
      else if (curr->equal && !curr->value)
        printf("%s=\n", curr->key);
		curr = curr->next;
	}
}
