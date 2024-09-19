/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:32:05 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/19 18:34:40 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_prompt(t_lst **cmd)
{
	char	*prompt;
	(void) cmd;
	// char	**cmds;
	// t_lst	*new;

	// new = NULL;
  // cmds = NULL;
	printf(CYAN);
	prompt = readline("Minishell>\033[0m ");
	if (prompt && *prompt)
	{
		add_history(prompt);
		// cmds = get_cmds_in_pipe(prompt);
		// add_cmd_to_lst(cmds, &cmd);
		// while((*cmd))
		// {

		// }
	}
	free(prompt);
}
