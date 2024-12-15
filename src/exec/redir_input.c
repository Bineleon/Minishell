/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:46:28 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 21:03:33 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	new_heredoc(t_data *data)
{
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->heredoc = gc_mem(MALLOC, sizeof(t_heredoc), NULL);
	data->heredoc->fullprompt = NULL;
	data->heredoc->in_process = true;
}

void	clean_heredoc(t_data *data)
{
	if (data->heredoc->fd[0] != -1)
		close(data->heredoc->fd[0]);
	if (data->heredoc->fd[1] != -1)
		close(data->heredoc->fd[1]);
	if (data->heredoc->fullprompt)
		gc_mem(FREE, 0, data->heredoc->fullprompt);
	data->heredoc = gc_mem(FREE, 0, data->heredoc);
}

void	save_stdin(int *stdi)
{
	*stdi = dup(STDIN_FILENO);
	if (!stdi)
		perror("dup");
}

void	restore_stdin(int *stdi)
{
	dup2(*stdi, STDIN_FILENO);
	close(*stdi);
}

int	redir_input(t_data *data, t_cmd *cmd)
{
	t_redir	*current_redir;
	int		fd;
	int		res;

	if (!cmd || !cmd->redir)
		return (1);
	current_redir = cmd->redir;
	fd = -1;
	while (current_redir)
	{
		if (current_redir->type == IN || current_redir->type == HEREDOC)
		{
			if (fd > 0)
				close_fd(&fd);
			res = new_input_fd(data, cmd, current_redir, &fd);
			if (res == 0 || res == 130)
				return (res);
		}
		current_redir = current_redir->next;
	}
	if (fd > 0)
		return (dup2(fd, cmd->fd_redir[0]), close(fd), 1);
	return (1);
}

// int	redir_input(t_data *data)
// {
// 	t_redir	*current_redir;
// 	int		fd;

// 	if (!data->cmds || !data->cmds->redir)
// 		return (0);
// 	current_redir = data->cmds->redir;
// 	fd = 0;
// 	while (current_redir)
// 	{
// 		if (current_redir->type == IN || current_redir->type == HEREDOC)
// 		{
// 			if (fd > 0)
// 			{
// 				close(fd);
// 				fd = 0;
// 			}
// 			if (new_input_fd(data, current_redir, &fd) == 0)
// 				return (2);
// ajouter gestion d'erreur en cas de non droits pour le fichier
// 		}
// 		current_redir = current_redir->next;
// 	}
// 	if (fd > 0)
// 		return (dup2(fd, STDIN_FILENO), close(fd), 1);
// 	return (0);
// }
