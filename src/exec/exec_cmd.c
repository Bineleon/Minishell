/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 22:26:27 by elilliu@stu       #+#    #+#             */
/*   Updated: 2024/10/21 23:25:59 by elilliu@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**all_paths(t_env *env)
{
	char	**paths;
	char	*str;

	if (!env->value)
		return (NULL);
	while (env->value)
	{
		if (ft_strncmp(env->value, "PATH=", 5) == 0)
		{
			str = ft_strtrim(env->value, "PATH");
			if (!str)
				return (NULL);
			paths = ft_split(str, ':');
			if (!paths)
				return (free(str), NULL);
			free(str);
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
			return (ft_free_tab(paths), NULL); // a remplacer avec le garbage collector
		if (access(str, F_OK | X_OK) == 0)
			return (ft_free_tab(paths), str); // idem
		free(str);
		i++;
	}
	return (ft_free_tab(paths), NULL); // idem
}

void	exec_cmd(t_data *data)
{
	char	*path;

	if (access(data->cmds->args[0], F_OK | X_OK) == 0)
		path = ft_strdup(data->cmds->args[0]);
	else
		path = new_path(data->cmds->args[0], data->envp_cpy); // voir si on peut utiliser la key pour trouver le bon path
	if (!path)
		error_mess(NULL, NULL);
	if (execve(path, data->cmds->args, data->envp_cpy) == -1) // remplacer env_cpy par la bonne valeur
		free(path);
}
