/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:26:27 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/12/15 21:53:58 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**all_paths(t_env *env)
{
	char	**paths;
	t_env	*tmp;

	tmp = env;
	if (!tmp->key)
		return (NULL);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, "PATH", 4) == 0)
		{
			paths = gc_split(tmp->value, ':');
			if (!paths)
				return (NULL);
			return (paths);
		}
		tmp = tmp->next;
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
		return (gc_mem(FREE, 0, paths), NULL);
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

static size_t	count_env(t_env *env)
{
	t_env	*tmp;
	size_t	i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_newenv(t_data *data)
{
	char	**newenv;
	t_env	*tmp;
	int		i;

	i = count_env(data->envp_cpy);
	tmp = data->envp_cpy;
	newenv = gc_mem(MALLOC, (i + 1) * sizeof(char *), NULL);
	newenv[i] = NULL;
	i = 0;
	while (tmp)
	{
		newenv[i] = joinequal(tmp->key, tmp->value);
		i++;
		tmp = tmp->next;
	}
	return (newenv);
}

void	exec_cmd(t_data *data)
{
	char	*path;
	char	**newenv;

	path = NULL;
	exec_no_cmd(data);
	exec_b_in_cmd(data);
	path_exec(data, &path);
	if (data->cmds->cmd && !path)
	{
		error_cmd(data->cmds->cmd);
		data->exit_status = 127;
		rl_clear_history();
		gc_mem(FULL_CLEAN, 0, NULL);
		gc_mem_env(FULL_CLEAN, 0, NULL);
		exit(data->exit_status);
	}
	if (path)
	{
		data->open_process = true;
		newenv = ft_newenv(data);
		if (!newenv)
			return ((void)gc_mem(FREE, 0, path));
		if (execve(path, data->cmds->args, newenv) == -1)
			gc_mem(FREE, 0, path);
	}
}
