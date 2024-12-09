/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:30:52 by neleon            #+#    #+#             */
/*   Updated: 2024/12/09 17:59:35 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_sigquit2(int sig)
{
  (void)sig;
  t_data *data;

  data = get_data();
  
}

static void	replace_redisplay(void)
{
	if (rl_on_new_line() != 0)
		return (perror("rl_on_new_line"));
	rl_replace_line("", 0);
	rl_redisplay();
}

static void sigint_process(void)
{
  t_data *data;

  data = get_data();
	signal(SIGINT, NULL);
	data->open_process = false;
  printf("\n");
  // ft_prompt(data);
}

static void sigint_herdeoc(void)
{
  t_data *data;

  data = get_data();
  data->heredoc = false;
  printf("\n");
  replace_redisplay();
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
  else if (!data->open_process)
  {
    printf("\n");
    replace_redisplay();
  }
  else
  {
    sigint_process();
  }
}

void	handle_signals(void)
{
  signal(SIGINT, &handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
