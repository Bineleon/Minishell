/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_redirection                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 00:36:51 by elilliu           #+#    #+#             */
/*   Updated: 2024/09/26 00:41:01 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			return (freetab(paths), NULL);
		if (access(str, F_OK | X_OK) == 0)
			return (freetab(paths), str);
		free(str);
		i++;
	}
	return (freetab(paths), NULL);
}

void	execute(t_data *data, t_cmd *cmd)
{
	char	*path;
	char	**args;

	args = jointab(cmd->cmd, cmd->args);
	if (!args)
		return ((void)printf("erreur malloc tableau blabla\n"));
	if (access(cmd->cmd, F_OK | X_OK) == 0)
		path = ft_strdup(cmd->cmd);
	else
		path = new_path(cmd->cmd, data->envp_cpy);
	if (!path)
		return ((void)freetab(args), (void)printf("message"
				"d'erreur blablabla\n"));
	if (execve(path, args, data->envp_cpy) == -1)
		return ((void)freetab(args), (void)printf("oui bon on a compris\n"));
	// demander si on peut mettre tout ca sur la meme ligne
}
