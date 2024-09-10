/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:30:52 by neleon            #+#    #+#             */
/*   Updated: 2024/09/10 18:56:16 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	s_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	// g_receiver = 1;
	if (signum == SIGINT)
		ft_prompt();
	// else if (signum == SIGINT)
	// 	exit(EXIT_SUCCESS);
}