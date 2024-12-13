/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:17:29 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/12 18:26:54 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	adding_new_redirs(t_cmd *cmds, t_fullcmd **current)
{
	while ((*current) && (*current)->type != PIPE)
	{
		if (is_redi((*current)))
		{
			if ((*current)->next && (*current)->next->type == WORD)
			{
				add_redir(&cmds->redir, (*current)->type,
					(*current)->next->str);
				(*current) = (*current)->next;
			}
		}
		(*current) = (*current)->next;
	}
}

void	create_new_cmd(t_cmd *cmds, t_fullcmd **current)
{
	int			i;
	t_fullcmd	*arg_check;

	i = 0;
	cmds->cmd = gc_strdup((*current)->str);
	arg_check = (*current);
	while (arg_check && arg_check->is_cmd)
	{
		i++;
		arg_check = arg_check->next;
	}
	cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
	i = 0;
	while ((*current) && (*current)->is_cmd)
	{
		cmds->args[i] = gc_strdup((*current)->str);
		i++;
		(*current) = (*current)->next;
	}
	cmds->args[i] = NULL;
}
