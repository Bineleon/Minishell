/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:39:12 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/10 19:44:36 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_output(t_data *data, t_cmd *cmd, int is_pipe)
{
	int	i;
	int	fd;

	i = 0;
	fd = 1;
	dup2(cmd->output, STDOUT_FILENO);
	if (is_pipe == true)
		dup2(data->fd[1], cmd->output);
	while (cmd->str[i])
	{
		if (ft_strncmp(str[i], ">") == 0)
		{
			if (fd && fd != 1 && fd != 2)
				close(fd);
			fd = open(str[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return ((void)printf("erreur open sortie\n"));
		}
		i++;
	}
	if (is_pipe == true)
		dup2(fd, data->fd[1]);
	else if (fd != 1)
		dup2(fd, cmd->output);
}

void	redir_input(t_data *data, t_cmd *cmd)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	dup2(cmd->input, STDIN_FILENO);
	while (cmd->str[i])
	{
		if (ft_strncmp(str[i], "<") == 0)
		{
			if (fd && fd != 1 && fd != 2)
				close(fd);
			fd = open(str[i + 1], O_RDONLY);
			if (fd == -1)
				return ((void)ft_putstr_fd("bash: \n", 2));
		}
		i++;
	}
	if (fd)
		dup2(fd, cmd->input);
}

void	exec_cmd(t_data *data, t_cmd *cmd, int is_pipe)
{
	redir_input(data, cmd);
	redir_output(data, cmd, is_pipe);
	execute(data, cmd);
}

int	redirection(t_data *data)
{
	while (data->cmds->next != NULL)
	{
		if (pipe(data->fd) == -1)
			return (error_mess(NULL, NULL), 0);
		data->pid = fork();
		if (data->pid == -1)
			return (error_mess(NULL, NULL), 0);
		if (data->pid == 0)
			exec_cmd(data, data->cmds, true);
		dup2(data->fd[0], data->cmds->next->input);
		close(data->fd[0]);
		close(data->fd[1]);
		data->cmds = data->cmds->next;
	}
}
