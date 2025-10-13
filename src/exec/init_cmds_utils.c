/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:17:29 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/15 20:25:33 by elilliu          ###   ########.fr       */
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

static int	count_args(t_fullcmd *current)
{
	int	count;

	count = 0;
	while (current)
	{
		if (current->is_cmd)
			count++;
		else if (is_redi(current) && current->next
			&& current->next->type == WORD)
			current = current->next;
		else if (current->type == PIPE)
			break ;
		current = current->next;
	}
	return (count);
}

static void	fill_args(t_cmd *cmds, t_fullcmd **current, char **args, int *index)
{
	while (*current)
	{
		if ((*current)->is_cmd)
		{
			args[*index] = gc_strdup((*current)->str);
			(*index)++;
		}
		else if (is_redi(*current) && (*current)->next
			&& (*current)->next->type == WORD)
		{
			add_redir(&cmds->redir, (*current)->type, (*current)->next->str);
			*current = (*current)->next;
		}
		else if ((*current)->type == PIPE)
			break ;
		*current = (*current)->next;
	}
	args[*index] = NULL;
}

void	create_new_cmd(t_cmd *cmds, t_fullcmd **current)
{
	int	i;
	int	arg_count;

	i = 0;
	cmds->cmd = gc_strdup((*current)->str);
	arg_count = count_args(*current);
	cmds->args = gc_mem(MALLOC, sizeof(char *) * (arg_count + 1), NULL);
	fill_args(cmds, current, cmds->args, &i);
}

int	is_last(t_fullcmd **fullcmd)
{
	t_fullcmd	*current;

	current = *fullcmd;
	while (current)
	{
		if (current->type == PIPE)
			return (0);
		current = current->next;
	}
	return (1);
}
