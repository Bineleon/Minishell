/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:11:41 by neleon            #+#    #+#             */
/*   Updated: 2024/12/10 21:53:43 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	free_tokens(t_data *data)
{
	t_fullcmd	*tmp;

	tmp = NULL;
	if (!data->token_fullcmd)
		return (NULL);
	while (data->token_fullcmd->next)
	{
		tmp = data->token_fullcmd;
		gc_mem(FREE, 0, tmp->str);
		data->token_fullcmd = data->token_fullcmd->next;
		free(tmp);
	}
	gc_mem(FREE, 0, data->token_fullcmd->str);
	gc_mem(FREE, 0, data->token_fullcmd);
	return (NULL);
}

static void	free_redi(t_cmd *cmd)
{
	t_redir	*tmp;

	tmp = NULL;
	if (!cmd->redir)
		return (NULL);
	while (cmd->redir->next)
	{
		tmp = cmd->redir;
		gc_mem(FREE, 0, tmp->file_name);
		cmd->redir = cmd->redir->next;
		free(tmp);
	}
	gc_mem(FREE, 0, cmd->redir->file_name);
	gc_mem(FREE, 0, cmd->redir);
	return (NULL);
}

static void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (NULL);
	while (args[i])
	{
		gc_mem(FREE, 0, &args[i]);
		i++;
	}
	gc_mem(FREE, 0, args);
}

static void	free_cmds(t_data *data)
{
	t_cmd	*tmp;

	tmp = NULL;
	while (data->cmds->next)
	{
		tmp = data->cmds;
		if (data->cmds->redir)
			free_redi(data->cmds);
		if (data->cmds->cmd)
		{
			free_args(data->cmds->args);
			gc_mem(FREE, 0, data->cmds->cmd);
		}
		data->cmds = data->cmds->next;
		free(tmp);
	}
	if (data->cmds->redir)
		free_redi(data->cmds);
	if (data->cmds->cmd)
	{
		free_args(data->cmds->args);
		gc_mem(FREE, 0, data->cmds->cmd);
	}
	gc_mem(FREE, 0, data->cmds);
	return (NULL);
}

void	full_free(t_data *data)
{
	if (data->cmds)
		free_cmds(data);
	if (data->token_fullcmd)
		free_tokens(data);
	if (data->delim)
		gc_mem(FREE, 0, data->delim);
}