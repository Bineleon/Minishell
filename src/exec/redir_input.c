/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:20:10 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/09 18:49:15 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(t_data *data, t_redir *current_redir)
{
	int		fd[2];
	char	*prompt;

	data->heredoc = true;
	if (pipe(fd) == -1)
		return ((void)error_mess(NULL, NULL));
	ft_putstr_fd("")
	while (1)
	{
		prompt = readline("heredoc> ");
		if (!prompt)
			return ((void)error_mess(NULL, NULL));
		if (ft_strncmp(current_redir->file_name, prompt,
				ft_strlen(current_redir->file_name + 1)) == 0)
		{
			free(prompt);
			break ;
		}
		free(prompt);
	}
	data->heredoc = false;
	dup2(fd[0], STDIN_FILENO);
}

void	redir_input(t_data *data)
{
	t_redir	*current_redir;
	int		fd;

	if (!data->cmds || data->cmds->redir)
		return ;
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
				return ;
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
