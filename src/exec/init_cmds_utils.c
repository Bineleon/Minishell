/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:17:29 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/15 17:21:06 by neleon           ###   ########.fr       */
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

// void	create_new_cmd(t_cmd *cmds, t_fullcmd **current)
// {
// 	int			i;
// 	t_fullcmd	*arg_check;

// 	i = 0;
// 	cmds->cmd = gc_strdup((*current)->str);
// 	arg_check = (*current);
// 	while (arg_check && arg_check->is_cmd)
// 	{
// 		i++;
// 		arg_check = arg_check->next;
// 	}
// 	cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
// 	i = 0;
// 	while ((*current) && (*current)->is_cmd)
// 	{
// 		cmds->args[i] = gc_strdup((*current)->str);
// 		i++;
// 		(*current) = (*current)->next;
// 	}
// 	cmds->args[i] = NULL;
// }

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

int	is_last(t_fullcmd **fullcmd, t_cmd *cmd)
{
	t_fullcmd	*current;

	current = *fullcmd;
	while (current && cmd->cmd && ft_strncmp(cmd->cmd, current->str,
			ft_strlen(cmd->cmd)) != 0)
		current = current->next;
	while (current)
	{
		if (current->type == PIPE)
			return (0);
		current = current->next;
	}
	return (1);
}

void	init_pipe(t_data *data, t_cmd *cmd, t_bool(is_first))
{
	if (is_first == false)
	{
		dup2(data->fd[1], cmd->fd_redir[0]);
		close(data->fd[0]);
		close(data->fd[1]);
	}
	if (is_last(&data->token_fullcmd, cmd) == 0)
	{
		if (pipe(data->fd) == -1)
		{
			error_mess(NULL, NULL);
			return ;
		}
		dup2(data->fd[0], cmd->fd_redir[1]);
	}
}
