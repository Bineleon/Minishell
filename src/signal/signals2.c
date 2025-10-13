/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:29:28 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 17:36:48 by neleon           ###   ########.fr       */
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
