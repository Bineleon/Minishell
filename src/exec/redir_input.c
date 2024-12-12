/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:20:10 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/12 15:34:01 by neleon           ###   ########.fr       */
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

void	heredoc(t_data *data, t_redir *current_redir)
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
		if (ft_strlen(current_redir->file_name) == ft_strlen(prompt)
			&& ft_strncmp(current_redir->file_name, prompt,
				ft_strlen(current_redir->file_name)) == 0)
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
	dup2(data->heredoc->fd[0], STDIN_FILENO);
	clean_heredoc(data);
}

int	redir_input(t_data *data)
{
	t_redir	*current_redir;
	int		fd;

	if (!data->cmds || !data->cmds->redir)
		return (0);
	current_redir = data->cmds->redir;
	fd = -1;
	while (current_redir)
	{
		if (fd > 0)
			close(fd);
		if (current_redir->type == IN)
		{
			fd = open(current_redir->file_name, O_RDONLY);
			if (fd == -1)
			{
				error_mess(NULL, current_redir->file_name);
				data->exit_status = 1;
				return (1);
			}
		}
		else if (current_redir->type == HEREDOC)
		{
			heredoc(data, current_redir);
			if (fd > 0)
				close(fd);
			fd = -1;
		}
		current_redir = current_redir->next;
	}
	if (fd > 0)
		dup2(fd, STDIN_FILENO);
	return (1);
}

// void	heredoc(t_data *data)
// {
// 	int		i;
// 	int		fd[2];
// 	char	*prompt;

// 	// printf("bonsoir\n\n");
// 	i = 0;
// 	while (data->cmds->str[i])
// 	{
// 		// printf("ce qu'on regarde: %s\n\n", data->cmds->str[i]);
// 		if (ft_strncmp(data->cmds->str[i], "<<", 3) == 0)
// 		{
// 			printf("suprise on a un heredoc\n\n");
// 			if (!data->cmds->str[i + 1])
// 				return ((void)error_mess(NULL, NULL));
// 			printf("on a trouve le delim\n");
// 			printf("le voila : %s\n", data->cmds->str[i + 1]);
// 			data->heredoc = true;
// 			data->delim = gc_strdup(data->cmds->str[i + 1]);
// 			printf("delim: %s\n", data->delim);
// 			if (pipe(fd) == -1)
// 				return ((void)error_mess(NULL, NULL));
// 			while (1)
// 			{
// 				prompt = readline("heredoc> ");
// 				if (!prompt)
// 				{
// 					printf(MAGENTA);
// 					printf("\e[4mCIAO BABY!\e[0m\n");
// 					printf(RESET);
// 					gc_mem(FULL_CLEAN, 0, NULL);
// 					exit(EXIT_SUCCESS);
// 				}
// 				if (ft_strncmp(data->delim, prompt, ft_strlen(data->delim) + 1) == 0)
// 				{
// 					free(prompt);
// 					break ;
// 				}
// 				ft_putstr_fd(prompt, fd[1]);
// 				free(prompt);
// 			}
// 			data->heredoc = false;
// 		}
// 		i++;
// 	}
// 	// printf("fd = %d\n", fd[0]);
// 	// dup2(fd[0], data->fd[0]);
// }

// void	redir_input(t_data *data)
// {
// 	int	i;
// 	int	fd;

// 	i = 0;
// 	fd = 0;
// 	while (data->cmds->str[i])
// 	{
// 		if (ft_strncmp(data->cmds->str[i], "<", 2) == 0)
// 		{
// 			printf("normalement on rentre jamais la\n\n");
// 			if (!data->cmds->str[i + 1])
// 				return ((void)error_mess(NULL, NULL));
// 			if (fd)
// 				close(fd);
// 			fd = open(data->cmds->str[i + 1], O_RDONLY);
// 			if (fd == -1)
// 				return ((void)error_mess(NULL, NULL));
// 		}
// 		i++;
// 	}
// 	if (fd && data->cmds->prev)
// 		dup2(fd, data->fd[0]);
// 	else if (fd)
// 		dup2(fd, STDIN_FILENO);
// }
