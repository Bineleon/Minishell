/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:57:19 by neleon            #+#    #+#             */
/*   Updated: 2024/09/13 16:57:44 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_envp_size(char **envp)
{
	int	envp_size;

	envp_size = 0;
	while (envp[envp_size])
		envp_size++;
	return (envp_size);
}

char	**cpy_envp(char **envp)
{
	int		size;
	int		i;
	char	**envp_cpy;

	i = 0;
	size = get_envp_size(envp);
	envp_cpy = (char **)malloc(size * sizeof(char *) + 1);
	if (!envp_cpy)
		return (NULL);
	while (envp[i])
	{
		envp_cpy[i] = ft_strdup(envp[i]);
		i++;
	}
	envp_cpy[i] = NULL;
	return (envp_cpy);
}