/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:06:18 by neleon            #+#    #+#             */
/*   Updated: 2024/09/12 19:53:00 by neleon           ###   ########.fr       */
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

char	**get_cmds_in_pipe(char *prompt)
{
	char	**pipe_split;

	pipe_split = ft_split(prompt, '|');
	return (pipe_split);
}
