/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:30:52 by neleon            #+#    #+#             */
/*   Updated: 2024/12/10 14:08:23 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_sigquit2(int sig)
{
  t_data *data;
  (void)sig;

  data = get_data();
  if (data->open_process)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		data->exit_status = 131;
	}
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
  t_data *data;

  data = get_data();
  signal(SIGINT, &handle_sigint);
  if (!data->open_process)
  {
    printf("ICI\n\n");
	  signal(SIGQUIT, SIG_IGN);
  }
}

void  signal_open_process(void)
{
  signal(SIGQUIT, &handle_sigquit2);
}
