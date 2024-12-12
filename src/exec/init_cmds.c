/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/12 21:38:10 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_redir(t_redir **redir_list, t_token type, char *file_name)
{
	t_redir	*new_redir;
	t_redir	*current;

	new_redir = gc_mem(MALLOC, sizeof(t_redir), NULL);
	new_redir->type = type;
	new_redir->file_name = gc_strdup(file_name);
	new_redir->next = NULL;
	if (*redir_list == NULL)
		*redir_list = new_redir;
	else
	{
		current = *redir_list;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
}

void	new_cmd(t_cmd *cmds, t_fullcmd **fullcmd)
{
	t_fullcmd	*current;

	current = *fullcmd;
	while (current && !current->is_cmd && current->type != PIPE)
	{
		if (is_redi(current))
		{
			if (current->next && current->next->type == WORD)
			{
				add_redir(&cmds->redir, current->type, current->next->str);
				current = current->next;
			}
		}
		current = current->next;
	}
	if (current && current->is_cmd)
		create_new_cmd(cmds, &current);
	adding_new_redirs(cmds, &current);
	*fullcmd = current;
}

void	sub_init_cmds(t_cmd *cmd, t_fullcmd **fullcmd, t_bool is_first)
{
	t_redir	*current_redir;
	int		fd;

	cmd->is_first = is_first;
	new_cmd(cmd, fullcmd);
	if (!cmd->cmd && cmd->redir)
	{
		current_redir = cmd->redir;
		while (current_redir)
		{
			if (current_redir->type == OUT)
				fd = open(current_redir->file_name,
						O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(current_redir->file_name,
						O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd == -1)
			{
				// error_mess(current_redir->file_name, NULL);
				return ;
			}
			else
				close(fd);
			current_redir = current_redir->next;
		}
	}
}

void	init_cmds(t_data *data)
{
	t_cmd		*cmdstmp;
	t_fullcmd	*fullcmdtmp;
	t_bool		is_first;

	data->fd[0] = -1;
	data->fd[1] = -1;
	data->fd[2] = -1;
	data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
	init_cmd(data->cmds);
	cmdstmp = data->cmds;
	fullcmdtmp = data->token_fullcmd;
	is_first = true;
	while (fullcmdtmp)
	{
		sub_init_cmds(cmdstmp, &fullcmdtmp, is_first);
		is_first = false;
		if (fullcmdtmp && fullcmdtmp->type == PIPE)
		{
			fullcmdtmp = fullcmdtmp->next;
			cmdstmp->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
			init_cmd(cmdstmp->next);
			cmdstmp->next->prev = cmdstmp;
			cmdstmp = cmdstmp->next;
		}
	}
	int i = 0;
	while (data->cmds->args[i])
	{
		printf("ARGS[i] : %s\n", data->cmds->args[i]);
		i++;
	}
}
