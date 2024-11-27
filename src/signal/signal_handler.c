/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:30:52 by neleon            #+#    #+#             */
/*   Updated: 2024/11/27 13:18:14 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_sigint(int sig)
{
  (void)sig;
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
