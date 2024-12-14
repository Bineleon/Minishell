/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 01:56:59 by neleon            #+#    #+#             */
/*   Updated: 2024/12/14 16:14:27 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_child_sigquit(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
	if (!data->open_process)
		return;
	data->exit_status = 131;
	ft_putstr_fd("\033[1;31mQuit (core dumped)\033[0m\n", 2);
}

void	handle_sigquit2(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();

	if (data->hd_active)
	{
		signal(SIGQUIT, SIG_IGN);
		return;
	}
	if (!data->open_process)
		return;
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

// static void	sigint_process(void)
// {
// 	t_data	*data;

// 	data = get_data();
// 	signal(SIGINT, NULL);
// 	data->open_process = false;
// 	printf("\n");
// }

void	handle_sigint(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
	data->exit_status = 130;
  if (!data->open_process)
	{
		replace_redisplay();
	}
	// else if (data->open_process)
	// {
	// 	sigint_process();
	// }
}

void	handle_signals(void)
{
	struct sigaction act;

	ft_bzero(&act, sizeof(act));
	act.sa_handler = handle_sigint;
	act.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &act, NULL) == -1)
		perror("sigaction");
	act.sa_handler = handle_sigquit2;
	if (sigaction(SIGQUIT, &act, NULL) == -1)
		perror("sigaction");
}

// void	signal_open_process(void)
// {
// 	signal(SIGQUIT, &handle_sigquit2);
// }
