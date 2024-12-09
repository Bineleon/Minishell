/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelbi <neleon@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:26:27 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/12/09 10:48:19 by nelbi            ###   ########.fr       */
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
	while (tmp) // while (tmp) au lieu de while (tmp->key)
	{
		if (ft_strncmp(tmp->key, "PATH", 4) == 0)
		{
			paths = ft_split(tmp->value, ':'); // a changer pour gc_split
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

  if (!data->cmds->cmd[0])     // in case "" or '' (empty cmd)
  {
      error_cmd(data->cmds->cmd);
      data->exit_status = 127;
      gc_mem(FULL_CLEAN, 0, NULL);
      exit(data->exit_status);
  }
	if (is_builtin(data->cmds->cmd))
	{
		exec_builtin(data, data->cmds);
		exit(data->exit_status);
	}
	if (access(data->cmds->cmd, F_OK | X_OK) == 0)
		path = gc_strdup(data->cmds->cmd);
	else
		path = new_path(data->cmds->cmd, data->envp_cpy);
	// printf("path = %s\n", path);
	if (!path)
	{
		data->exit_status = 127;
		error_cmd(data->cmds->cmd);
		gc_mem(FULL_CLEAN, 0, NULL);
		exit(data->exit_status);
	}
	newenv = ft_newenv(data);
	if (!newenv)
		return ((void)gc_mem(FREE, 0, path));
	if (execve(path, data->cmds->args, newenv) == -1)
		gc_mem(FREE, 0, path);
}

// void	exec_cmd(t_data *data)
// {
// 	char	*path;
// 	char	**newenv;

// 	if (is_builtin(data->cmds->cmd))
// 	{
// 		exec_builtin(data, data->cmds);
// 		exit(data->exit_status);
// 	}
// 	if (access(data->cmds->args[0], F_OK | X_OK) == 0)
// 	{
// 		path = gc_strdup(data->cmds->args[0]);
// 	}
// 	else
// 		path = new_path(data->cmds->args[0], data->envp_cpy);
// 	// printf("path = %s\n", path);
// 	if (!path)
// 	{
// 		data->exit_status = 127;
// 		error_cmd(data->cmds->args[0]);
// 		gc_mem(FULL_CLEAN, 0, NULL);
// 		exit(data->exit_status);
// 	}
// 	newenv = ft_newenv(data);
// 	if (!newenv)
// 		return ((void)gc_mem(FREE, 0, path));
// 	if (execve(path, data->cmds->args, newenv) == -1)
// 		gc_mem(FREE, 0, path);
// }
