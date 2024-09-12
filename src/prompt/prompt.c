/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:32:05 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/12 19:47:16 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_prompt(t_lst **cmd)
{
	char	*prompt;
	(void) cmd;
	// char	**cmd_args;
	// t_lst	*new;
	
	// new = NULL;
	printf(CYAN);
	prompt = readline("Minishell>\033[0m ");
	if (prompt && *prompt)
	{
		add_history(prompt);
		// cmd_args = ft_split(prompt, ' ');
		// new = ft_lstnew(cmd_args);
		// ft_lstadd_back(cmd, new);
	}
	free(prompt);
}
