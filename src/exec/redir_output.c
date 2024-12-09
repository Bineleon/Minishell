/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/09 17:32:15 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	new_fd(char *operator, char *file)
{
	int	fd;

	fd = 0;
	if (ft_strncmp(operator, ">", 2) == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = open(file, O_APPEND | O_CREAT, 0644);
	return (fd);
}

void	redir_builtins(t_data *data)
{
	t_redir	*current_redir;
	int		fd;

	if (!data->cmds || !data->cmds->redir)
		return ;
	current_redir = data->cmds->redir;
	fd = -1;
	while (current_redir)
	{
		if (current_redir->type == OUT || current_redir->type == APPEND)
		{
			if (fd > 0)
			{
				close(fd);
			}
			if (current_redir->type == OUT)
			{
				fd = open(current_redir->file_name,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
				printf("fd : %d\n\n", fd);
			}
			else if (current_redir->type == APPEND)
				fd = open(current_redir->file_name, O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				error_mess(NULL, current_redir->file_name);
				data->exit_status = 1;
				return ;
			}
		}
		current_redir = current_redir->next;
	}
	if (fd > 0)
	{
		data->fd_ = fd;
		// close(fd); // A voir
	}
}

void	redir_output(t_data *data, t_cmd *cmd)
{
	t_redir	*current_redir;
	int		fd;

	if (!cmd || !cmd->redir)
		return ;
	current_redir = cmd->redir;
	fd = -1;
	while (current_redir)
	{
		if (current_redir->type == OUT || current_redir->type == APPEND)
		{
			if (fd > 0)
				close(fd);
			if (current_redir->type == OUT)
				fd = open(current_redir->file_name,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else if (current_redir->type == APPEND)
				fd = open(current_redir->file_name, O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				error_mess(NULL, current_redir->file_name);
				data->exit_status = 1;
				return ;
			}
		}
		current_redir = current_redir->next;
	}
	if (fd > 0)
		dup2(fd, STDOUT_FILENO);
}

// void	redir_output(t_data *data)
// {
// 	int	i;
// 	int	fd;

// 	i = 0;
// 	fd = 0;
// 	while (data->cmds->str[i])
// 	{
// 		if (ft_strncmp(data->cmds->str[i], ">", 2) == 0
// 			|| ft_strncmp(data->cmds->str[i], ">>", 3) == 0)
// 		{
// 			if (!data->cmds->str[i + 1])
// 				return ((void)error_mess(NULL, NULL));
// 			if (fd)
// 				close(fd);
// 			fd = new_fd(data->cmds->str[i], data->cmds->str[i + 1]);
// 			if (fd == -1)
// 				return ((void)error_mess(NULL, NULL));
// 		}
// 		i++;
// 	}
// 	if (fd && data->cmds->next)
// 		dup2(fd, data->fd[1]);
// 	else if (fd)
// 		dup2(fd, STDOUT_FILENO);
// }
