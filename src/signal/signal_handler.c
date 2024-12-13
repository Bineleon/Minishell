/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/13 21:33:38 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigquit2(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
  data->exit_status = 131;
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

static void	replace_redisplay2(void)
{
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDIN_FILENO);
	if (rl_on_new_line() != 0)
		return (perror("rl_on_new_line"));
	rl_redisplay();

}

static void	sigint_process(void)
{
	t_data	*data;

	data = get_data();
	signal(SIGINT, NULL);
	data->open_process = false;
	printf("\n");
	// ft_prompt(data);
}

// static void	sigint_herdeoc(void)
// {
// 	t_data	*data;

// 	data = get_data();
//   signal(SIGQUIT, SIG_IGN);
//   data->open_process = false;
//   data->heredoc->in_process = false;
// 	clean_heredoc(data);
//   gc_mem(FULL_CLEAN, 0, NULL);
//   // exit(data->exit_status);
// 	printf("\n");
// 	replace_redisplay();
//   printf("\b\b");
// 	ft_prompt(data);
// }

static void	handle_sigint2(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
	data->exit_status = 130;
	replace_redisplay2();
}

static void	handle_sigint(int sig)
{
	t_data	*data;

	(void)sig;
	data = get_data();
	data->exit_status = 130;
  if (!data->open_process)
	{
		replace_redisplay();
	}
	else
	{		// ft_putstr_fd("ICI\n", 2);
		sigint_process();
	}
}

void	handle_signals2(void)
{
	signal(SIGINT, &handle_sigint2);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signals(void)
{
	// t_data	*data;

	// data = get_data();
	signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, &handle_sigquit2);

}

// void	signal_open_process(void)
// {
// 	signal(SIGQUIT, &handle_sigquit2);
// }
