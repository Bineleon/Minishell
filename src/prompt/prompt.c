/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                    content                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:32:05 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/19 19:19:58 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_prompt(void)
{
	char	*prompt;
	// char	**cmds;
	// t_lst	*new;

	// new = NULL;
  // cmds = NULL;
	printf(CYAN);
	prompt = readline("Minishell>\033[0m ");
	if (prompt && *prompt)
	{
		add_history(prompt);
    check_open_quotes(prompt);
		// cmds = get_cmds_in_pipe(prompt);
		// add_cmd_to_lst(cmds, &cmd);
		// while((*cmd))
		// {

		// }
	}
	free(prompt);
}
