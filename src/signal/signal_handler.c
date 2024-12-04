/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:30:52 by neleon            #+#    #+#             */
/*   Updated: 2024/12/04 11:58:37 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void sigint_parent(int sig)
// {
//   t_data *data;
//   (void)sig;

//   data = get_data();
// }

// void sigint_child(int sig)
// {
//   t_data *data;
//   (void)sig;

//   data = get_data();
// }

void sigint_herdeoc()
{
  t_data *data;

  data = get_data();
  data->heredoc = false;
  printf("\n");
  if (rl_on_new_line() != 0)
		return (perror("rl_on_new_line"));
  // printf(CYAN);
	rl_replace_line("", 0);
  ft_prompt(data);
}

void	handle_sigint(int sig)
{
  t_data *data;
  (void)sig;

  data = get_data();
  data->exit_status = 130;
  if (data->heredoc)
    sigint_herdeoc();
  printf("\n");
	if (rl_on_new_line() != 0)
		return (perror("rl_on_new_line"));
  printf(CYAN);
	rl_replace_line("", 0);
	rl_redisplay();
  printf(RESET);
}

void	handle_signals(void)
{
  signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
