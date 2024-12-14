/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:55:12 by neleon            #+#    #+#             */
/*   Updated: 2024/12/14 01:13:32 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_valid_key(char *key)
{
	int	i;

	i = 1;
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (false);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

size_t	get_env_size(t_env *env)
{
	size_t	env_size;
	t_env	*curr;

	curr = env;
	env_size = 0;
	while (curr)
	{
		env_size++;
		curr = curr->next;
	}
	return (env_size);
}

void	swap_env(t_env *a, t_env *b)
{
	t_env	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_longest(char *s1, char *s2)
{
	int	len_1;
	int	len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	if (len_1 > len_2)
		return (len_1);
	return (len_2);
}

void	sort_env(t_env **arr)
{
	int	i;
	int	j;

	i = 0;
	if (!arr)
		return ;
	while (arr[i + 1])
	{
		j = i + 1;
		while (arr[j])
		{
			if (ft_strncmp(arr[i]->key, arr[j]->key, ft_longest(arr[i]->key,
						arr[j]->key)) > 0)
				swap_env(arr[i], arr[j]);
			j++;
		}
		i++;
	}
}
