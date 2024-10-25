/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:26:27 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/10/23 14:56:49 by elilliu@stu      ###   ########.fr       */
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
			return (gc_mem(FREE, 0, paths), NULL); // a remplacer avec le garbage collector
		if (access(str, F_OK | X_OK) == 0)
			return (gc_mem(FREE, 0, paths), str); // idem
		free(str);
		i++;
	}
	return (gc_mem(FREE, 0, paths), NULL); // idem
}

void	exec_cmd(t_data *data)
{
	char	*path;

	if (access(data->cmds->args[0], F_OK | X_OK) == 0)
		path = ft_strdup(data->cmds->args[0]);
	else
		path = new_path(data->cmds->args[0], data->envp_cpy);
	if (!path)
		error_mess(NULL, NULL);
	// if (execve(path, data->cmds->args, data->envp_cpy) == -1) // remplacer env_cpy par la bonne valeur
	// 	free(path);
}
