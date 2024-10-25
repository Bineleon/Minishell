/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:26:27 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/10/25 19:55:27 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**all_paths(t_env *env)
{
	char	**paths;

	if (!env->key)
		return (NULL);
	while (env->key)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
		{
			paths = ft_split(env->value, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		env = env->next;
	}
	return (NULL);
}

char	*new_path(char *arg, t_env *env_cpy)
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	paths = all_paths(env_cpy);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		str = join(paths[i], arg);
		if (!str)
			return (gc_mem(FREE, 0, paths), NULL);
		if (access(str, F_OK | X_OK) == 0)
			return (gc_mem(FREE, 0, paths), str);
		gc_mem(FREE, 0, str);
		i++;
	}
	return (gc_mem(FREE, 0, paths), NULL);
}

char	**ft_newenv(t_data *data)
{
	char	**newenv;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = data->envp_cpy;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	newenv = gc_mem(MALLOC, i + 1, NULL);
	i = 0;
	while (data->envp_cpy)
	{
		newenv[i] = joinequal(data->envp_cpy->key, data->envp_cpy->value);
		i++;
		data->envp_cpy = data->envp_cpy->next;
	}
	return (newenv);
}

void	exec_cmd(t_data *data)
{
	char	*path;
	char	**newenv;

	if (access(data->cmds->args[0], F_OK | X_OK) == 0)
		path = ft_strdup(data->cmds->args[0]);
	else
		path = new_path(data->cmds->args[0], data->envp_cpy);
	if (!path)
		error_mess(NULL, NULL);
	newenv = ft_newenv(data);
	if (!newenv)
		return ((void)gc_mem(FREE, 0, path));
	if (execve(path, data->cmds->args, newenv) == -1)
		gc_mem(FREE, 0, path);
}
