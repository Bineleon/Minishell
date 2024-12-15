/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/15 13:59:31 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigquit2(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
	if (data->open_process)
	{
		data->exit_status = 131;
		ft_putstr_fd("\033[1;31mQuit (core dumped)\033[0m\n", 2);
	}
}

static void	replace_redisplay(void)
{
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDIN_FILENO);
	printf(CYAN);
	if (rl_on_new_line() != 0)
		return (perror("rl_on_new_line"));
	rl_redisplay();
	printf(RESET);
}

static void	sigint_process(void)
{
	t_data	*data;

	printf("SIGIN\n\n");
	data = get_data();
	data->sig = 130;
	data->exit_status = data->sig;
	data->open_process = false;
	signal(SIGINT, NULL);
	printf("\n");
}

static void	sigint_heredoc(void)
{
	t_data	*data;

	data = get_data();
	data->sig = 130;
	data->exit_status = data->sig;
	printf("\n");
	clean_heredoc(data);
	close(STDIN_FILENO);
}

void	handle_sigint(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
	data->exit_status = 130;
	if (data->heredoc && data->heredoc->in_process)
	{
		sigint_heredoc();
	}
	else if (!data->open_process)
		replace_redisplay();
	else if (data->open_process)
		sigint_process();
}

void	handle_signals(void)
{
	t_data	*data;

	data = get_data();
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit2);
}
