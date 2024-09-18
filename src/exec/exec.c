/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 17:44:58 by elilliu           #+#    #+#             */
/*   Updated: 2024/09/18 18:34:56 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	row;

	row = 0;
	while (tab[row])
		free(tab[row++]);
	free(tab);
}

char	*join(char *path, char *name)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, name);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (str);
}

char	**all_paths(char **env)
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	if (!env[i])
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			str = ft_strtrim(env[i], "PATH");
			if (!str)
				return (NULL);
			paths = ft_split(str, ':');
			if (!paths)
				return (free(str), NULL);
			free(str);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*new_path(char *av, char **env)
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	paths = all_paths(env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		str = join(paths[i], av);
		if (!str)
			return (ft_free_tab(paths), NULL);
		if (access(str, F_OK | X_OK) == 0)
			return (ft_free_tab(paths), str);
		free(str);
		i++;
	}
	return (ft_free_tab(paths), NULL);
}

char	**join_tabs(char *str, char **tab)
{
	char	**new_tab;
	int		i;

	i = 0;
	while (tab[i + 1])
		i++;
	while (i >= 0)
	{
		tab[i + 1] = ft_strdup(tab[i]);
		if (!tab[i + 1])
			return (ft_free_tab(paths), )
		free(tab[i]);
		i--;
	}
	tab[0] = ft_strdup(str);
}

int	execution(t_cmd **cmd, char **env)
{
	char	*path;
	char	**args;
void	ft_free_tab(char **tab)
{
	int	row;

	row = 0;
	while (tab[row])
		free(tab[row++]);
	free(tab);
}

char	*join(char *path, char *name)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, name);
	if (!str)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (str);
}

char	**all_paths(char **env)
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	if (!env[i])
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			str = ft_strtrim(env[i], "PATH");
			if (!str)
				return (NULL);
			paths = ft_split(str, ':');
			if (!paths)
				return (free(str), NULL);
			free(str);
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*new_path(char *av, char **env)
{
	char	**paths;
	char	*str;
	int		i;

	i = 0;
	paths = all_paths(env);
	if (!paths)
		return (NULL);
	while (paths[i])
	{
		str = join(paths[i], av);
		if (!str)
			return (ft_free_tab(paths), NULL);
		if (access(str, F_OK | X_OK) == 0)
			return (ft_free_tab(paths), str);
		free(str);
		i++;

	if (access(cmd->cmd, F_OK | X_OK) == 0)
		path = ft_strdup(cmd->cmd);
	else
		path = new_path(cmd->cmd, env);
	if (!path)
		error_cmd();
	if (execve(path, ))
}

int	exec(t_lst *lst)
{
	while (lst->next)
	{
		execution(lst->cmd, lst->copie_envp);
		lst = lst->next;
	}
	return (1);
}
