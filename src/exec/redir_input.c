/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:20:10 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/14 17:21:42 by elilliu@stu      ###   ########.fr       */
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
		gc_mem(FREE, (size_t) NULL, data->heredoc->fullprompt);
	gc_mem(FREE, (size_t) NULL, data->heredoc);
}

void	heredoc(t_data *data, t_cmd *cmd, t_redir *current_redir)
{
	char	*prompt;

	new_heredoc(data);
	if (pipe(data->heredoc->fd) == -1)
		return ((void)clean_heredoc(data), (void)error_mess(NULL, NULL));
	prompt = NULL;
	while (1)
	{
		prompt = readline("> ");
		if (!prompt)
			return ((void)error_mess(NULL, NULL));
		if (is_delim(current_redir, prompt) == 1)
		{
			gc_mem(FREE, (size_t) NULL, prompt);
			break ;
		}
		data->heredoc->fullprompt = gc_strjoin(data->heredoc->fullprompt,
				prompt);
		gc_mem(FREE, (size_t) NULL, prompt);
		data->heredoc->fullprompt = gc_strjoin(data->heredoc->fullprompt, "\n");
	}
	ft_putstr_fd(data->heredoc->fullprompt, data->heredoc->fd[1]);
	dup2(data->heredoc->fd[0], cmd->fd_redir[0]);
	clean_heredoc(data);
}

int	redir_input(t_data *data, t_cmd *cmd)
{
	t_redir *current_redir;
	int		fd;

	if (!cmd || !cmd->redir)
		return (1);
	current_redir = cmd->redir;
	fd = 0;
	while(current_redir)
	{
		if (current_redir->type == IN || current_redir->type == HEREDOC)
		{
			if (fd > 0)
			{
				close(fd);
				fd = 0;
			}
			if (new_input_fd(data, cmd, current_redir, &fd) == 0)
				return (0);
		}
		current_redir = current_redir->next;
	}
	if (fd > 0)
		dup2(fd, cmd->fd_redir[0]);
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
// 				return (2); // ajouter gestion d'erreur en cas de non droits pour le fichier
// 		}
// 		current_redir = current_redir->next;
// 	}
// 	if (fd > 0)
// 		return (dup2(fd, STDIN_FILENO), close(fd), 1);
// 	return (0);
// }
