/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelbi <neleon@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/09 10:56:10 by nelbi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void add_redir(t_redir **redir_list, t_token type, char *file_name)
{
    t_redir *new_redir;
    t_redir *current;

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

void new_cmd(t_cmd *cmds, t_fullcmd **fullcmd)
{
    int i = 0;
    t_fullcmd *current;
    t_fullcmd *tmp;

    current = *fullcmd;
    while (current && !current->is_cmd)
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
    if (!current)
        return;
    cmds->cmd = gc_strdup(current->str);
    tmp = current;
    while (tmp && tmp->is_cmd)
    {
        i++;
        tmp = tmp->next;
    }
    cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
    i = 0;
    while (current && current->is_cmd)
    {
        cmds->args[i++] = gc_strdup(current->str);
        current = current->next;
    }
    cmds->args[i] = NULL;
    *fullcmd = current;
}

void new_str(t_cmd *cmds, t_fullcmd **fullcmd)
{
    int i = 0;
    t_fullcmd *current;

    current = *fullcmd;
    while (cmds->args[i])
        i++;
    cmds->str = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
    i = 0;
    while (cmds->args[i])
    {
        cmds->str[i] = gc_strdup(cmds->args[i]);
        i++;
    }
    while (current && current->type != PIPE)
    {
        if (is_redi(current))
        {
            if (current->next && current->next->type == WORD)
            {
                add_redir(&cmds->redir, current->type, current->next->str);
                current = current->next;
            }
        }
        else
            cmds->str[i++] = gc_strdup(current->str);
        current = current->next;
    }
    cmds->str[i] = NULL;
    *fullcmd = current;
}

void init_cmds(t_data *data)
{
    t_cmd *cmdstmp;
    t_fullcmd *fullcmdtmp;

    data->fd[0] = -1;
    data->fd[1] = -1;
    data->fd[2] = -1;
    data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
    init_cmd(data->cmds);
    cmdstmp = data->cmds;
    fullcmdtmp = data->token_fullcmd;
    while (fullcmdtmp)
    {
        new_cmd(cmdstmp, &fullcmdtmp);
        new_str(cmdstmp, &fullcmdtmp);
        if (fullcmdtmp && fullcmdtmp->type == PIPE)
        {
            fullcmdtmp = fullcmdtmp->next;
            cmdstmp->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
            init_cmd(cmdstmp->next);
            cmdstmp->next->prev = cmdstmp;
            cmdstmp = cmdstmp->next;
        }
    }
}

// void	new_str(t_cmd *cmds, t_fullcmd **fullcmd)
// {
// 	int			i;
// 	t_fullcmd	*firstcmd;

// 	i = 0;
// 	firstcmd = *fullcmd;
// 	while (cmds->args[i])
// 	{
// 		// printf("cmd = %s\n", cmds->args[i]);
// 		i++;
// 	}
// 	while (*fullcmd && (*fullcmd)->type != PIPE)
// 	{
// 		i++;
// 		*fullcmd = (*fullcmd)->next;
// 	}
// 	cmds->str = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
// 	i = 0;
// 	// printf("cmd args [i] = %s\n", cmds->args[i]);
// 	cmds->str[i] = gc_strdup(cmds->args[i]);
// 	while (cmds->args[++i])
// 		cmds->str[i] = gc_strdup(cmds->args[i]);
// 	*fullcmd = firstcmd;
// 	while (*fullcmd && (*fullcmd)->type != PIPE)
// 	{
// 		cmds->str[i++] = gc_strdup((*fullcmd)->str);
// 		*fullcmd = (*fullcmd)->next;
// 	}
// 	cmds->str[i] = NULL;
// }

// void	new_cmd(t_cmd *cmds, t_fullcmd **fullcmd)
// {
// 	int			i;
// 	t_fullcmd	*firstcmd;

// 	i = 0;
// 	firstcmd = *fullcmd;
// 	while (*fullcmd && (*fullcmd)->type != PIPE && (*fullcmd)->type != IN
// 		&& (*fullcmd)->type != OUT)
// 	{
// 		i++;
// 		*fullcmd = (*fullcmd)->next;
// 	}
// 	cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
// 	cmds->cmd = gc_strdup(firstcmd->str);
// 	i = 0;
// 	*fullcmd = firstcmd;
// 	while (*fullcmd && (*fullcmd)->type != PIPE && (*fullcmd)->type != IN
// 		&& (*fullcmd)->type != OUT)
// 	{
// 		cmds->args[i] = gc_strdup((*fullcmd)->str);
// 		i++;
// 		*fullcmd = (*fullcmd)->next;
// 	}
// 	cmds->args[i] = NULL;
// }

// void	init_cmds(t_data *data)
// {
// 	t_cmd		*cmdstmp;
// 	t_fullcmd	*fullcmdtmp;

// 	data->fd[0] = -1;
// 	data->fd[1] = -1;
// 	data->fd[2] = -1;
// 	data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
// 	init_cmd(data->cmds);
// 	cmdstmp = data->cmds;
// 	fullcmdtmp = data->token_fullcmd;
// 	while (fullcmdtmp)
// 	{
// 		new_cmd(cmdstmp, &fullcmdtmp);
// 		new_str(cmdstmp, &fullcmdtmp);
// 		if (fullcmdtmp && fullcmdtmp->type == PIPE)
// 		{
// 			fullcmdtmp = fullcmdtmp->next;
// 			cmdstmp->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
// 			init_cmd(cmdstmp->next);
// 			cmdstmp->next->prev = cmdstmp;
// 			cmdstmp = cmdstmp->next;
// 		}
// 	}
// }
