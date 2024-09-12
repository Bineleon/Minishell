/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:32:05 by bineleon          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/10 18:23:07 by elilliu          ###   ########.fr       */
=======
/*   Updated: 2024/09/12 15:55:23 by bineleon         ###   ########.fr       */
>>>>>>> master
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void  ft_prompt(t_lst **cmd)
{
  char *prompt;
  char **cmd_args;
  t_lst *new;

  new = NULL;
  printf(CYAN);
  prompt = readline("Minishell>\033[0m ");
  if (prompt && *prompt)
  {
    add_history(prompt);
    cmd_args = ft_split(prompt, ' ');
    new = ft_lstnew(cmd_args);
		ft_lstadd_back(cmd, new);
  }
  free(prompt);
}
