/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 16:05:59 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/15 20:23:59 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_minishell(char *cmd)
{
	if (cmd && (ft_strcmp(cmd, "./minishell") == 0 || ft_strcmp(cmd,
				"minishell") == 0))
		return (true);
	return (false);
}

t_bool	check_minishell_cmd(t_data *data)
{
	t_cmd	*current;

	current = data->cmds;
	if (current->cmd && current->next)
	{
		if (check_minishell(current->cmd))
			return (true);
	}
	current = current->next;
	while (current)
	{
		if (check_minishell(current->cmd))
			return (true);
		current = current->next;
	}
	return (false);
}

int	verif_interactive_mode(t_data *data)
{
	t_cmd	*current;

	current = data->cmds;
	if (check_minishell_cmd(data))
	{
		printf(RED);
		ft_putstr_fd("\033[1;31mminishell :"
						"interactive mode not allowed 💩\033[0m\n",
						2);
		printf(RESET);
		while (current)
		{
			close(current->fd_redir[0]);
			close(current->fd_redir[1]);
			current = current->next;
		}
		data->exit_status = 127;
		return (0);
	}
	return (1);
}

void	finish_process(t_data *data)
{
	close(data->cmds->fd_redir[0]);
	close(data->cmds->fd_redir[1]);
	data->open_process = true;
}
