/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:45:31 by neleon            #+#    #+#             */
/*   Updated: 2024/11/25 15:45:37 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd(t_env *env, char *oldpwd)
{
	char	buf[PATH_MAX];

	if (!getcwd(buf, PATH_MAX))
	{
		perror("getcwd(): ");
		return ;
	}
	update_env(&env, "OLDPWD", oldpwd, true);
	update_env(&env, "PWD", buf, true);
}

static t_bool	check_args_err(t_data *data)
{
	if (data->cmds->args[1] && data->cmds->args[2])
	{
		printf("minishell: cd: too many arguments\n");
		data->exit_status = 1;
		return (true);
	}
	if (!data->cmds->args[1])
	{
		printf("minishell: cd: missing argument\n");
		data->exit_status = 1;
		return (true);
	}
	return (false);
}

void	ft_cd(t_data *data)
{
	char	oldpwd[PATH_MAX];

	if (check_args_err(data))
		return ;
	if (!getcwd(oldpwd, PATH_MAX))
	{
		perror("getcwd(): ");
		data->exit_status = 1;
		return ;
	}
	if (chdir(data->cmds->args[1]) == -1)
	{
		perror(data->cmds->args[1]);
		data->exit_status = 1;
		return ;
	}
	update_pwd(data->envp_cpy, oldpwd);
	data->exit_status = 0;
}
