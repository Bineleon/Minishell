/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:45:31 by neleon            #+#    #+#             */
/*   Updated: 2024/12/07 18:02:03 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd(t_env *env, char *oldpwd)
{
	char	buf[PATH_MAX];
	t_data	*data;

	data = get_data();
	if (!getcwd(buf, PATH_MAX))
	{
		perror("getcwd(): ");
		data->exit_status = 1;
		return ;
	}
	update_env(&env, "OLDPWD", oldpwd, true);
	update_env(&env, "PWD", buf, true);
	data->exit_status = 0;
}

static t_bool	check_args_err(t_cmd *cmds)
{
	t_data	*data;

	data = get_data();
	if (cmds->args[1] && cmds->args[2])
	{
		error_mess("cd", "too many arguments\n");
		data->exit_status = 1;
		return (true);
	}
	if (!cmds->args[1])
	{
		error_mess("cd", "missing argument\n");
		data->exit_status = 1;
		return (true);
	}
	return (false);
}

void	ft_cd(t_cmd *cmds)
{
	char	oldpwd[PATH_MAX];
	t_data	*data;

	data = get_data();
	if (check_args_err(cmds))
		return ;
	if (!getcwd(oldpwd, PATH_MAX))
	{
		ft_putstr_fd("minishell: ", 2);
		perror("getcwd(): ");
		data->exit_status = 1;
		return ;
	}
	if (chdir(cmds->args[1]) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		perror(cmds->args[1]);
		data->exit_status = 1;
		return ;
	}
	update_pwd(data->envp_cpy, oldpwd);
	data->exit_status = 0;
}
