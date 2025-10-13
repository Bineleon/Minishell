/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:51:54 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 22:16:56 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	clear_exec(t_data *data)
{
	rl_clear_history();
	gc_mem(FULL_CLEAN, 0, NULL);
	gc_mem_env(FULL_CLEAN, 0, NULL);
	exit(data->exit_status);
}

void	exec_no_cmd(t_data *data)
{
	if (data->cmds->cmd && ft_strlen(data->cmds->cmd) < 1 && !data->cmds->redir)
	{
		error_cmd(data->cmds->cmd);
		data->exit_status = 127;
		clear_exec(data);
	}
}

void	exec_b_in_cmd(t_data *data)
{
	if (data->cmds->cmd && is_builtin(data->cmds->cmd))
	{
		if (redir_builtins(data) == 0)
			clear_exec(data);
		exec_builtin(data, data->cmds);
		clear_exec(data);
	}
}

void	path_exec(t_data *data, char **path)
{
	if (data->cmds->cmd && access(data->cmds->cmd, F_OK | X_OK) == 0)
		*path = gc_strdup(data->cmds->cmd);
	else if (data->cmds->cmd && ft_strchr(data->cmds->cmd, '/')
		&& access(data->cmds->cmd, F_OK | X_OK) != 0)
	{
		error_mess(data->cmds->cmd, "No such file or directory");
		data->exit_status = 127;
		clear_exec(data);
	}
	else
	{
		if (data->cmds->cmd)
			*path = new_path(data->cmds->cmd, data->envp_cpy);
		else
			clear_exec(data);
	}
}
