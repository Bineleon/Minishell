/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:20:10 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/06 14:51:29 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc(t_data *data)
{
	int		i;
	int		fd[2];
	char	*prompt;

	// printf("bonsoir\n\n");
	i = 0;
	while (data->cmds->str[i])
	{
		// printf("ce qu'on regarde: %s\n\n", data->cmds->str[i]);
		if (ft_strncmp(data->cmds->str[i], "<<", 3) == 0)
		{
			printf("suprise on a un heredoc\n\n");
			if (!data->cmds->str[i + 1])
				return ((void)error_mess(NULL, NULL));
			printf("on a trouve le delim\n");
			printf("le voila : %s\n", data->cmds->str[i + 1]);
			data->heredoc = true;
			data->delim = gc_strdup(data->cmds->str[i + 1]);
			printf("delim: %s\n", data->delim);
			if (pipe(fd) == -1)
				return ((void)error_mess(NULL, NULL));
			while (1)
			{
				prompt = readline("heredoc> ");
				if (!prompt)
				{
					printf(MAGENTA);
					printf("\e[4mCIAO BABY!\e[0m\n");
					printf(RESET);
					gc_mem(FULL_CLEAN, 0, NULL);
					exit(EXIT_SUCCESS);
				}
				if (ft_strncmp(data->delim, prompt, ft_strlen(data->delim) + 1) == 0)
				{
					free(prompt);
					break ;
				}
				ft_putstr_fd(prompt, fd[1]);
				free(prompt);
			}
			data->heredoc = false;
		}
		i++;
	}
	// printf("fd = %d\n", fd[0]);
	// dup2(fd[0], data->fd[0]);
}

void	redir_input(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (data->cmds->str[i])
	{
		if (ft_strncmp(data->cmds->str[i], "<", 2) == 0)
		{
			printf("normalement on rentre jamais la\n\n");
			if (!data->cmds->str[i + 1])
				return ((void)error_mess(NULL, NULL));
			if (fd)
				close(fd);
			fd = open(data->cmds->str[i + 1], O_RDONLY);
			if (fd == -1)
				return ((void)error_mess(NULL, NULL));
		}
		i++;
	}
	if (fd && data->cmds->prev)
		dup2(fd, data->fd[0]);
	else if (fd)
		dup2(fd, STDIN_FILENO);
}
