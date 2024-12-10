/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/12/10 13:51:42 by bineleon         ###   ########.fr       */
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
	int			i;
	t_fullcmd	*current;
  t_fullcmd *arg_check;

	i = 0;
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
	{
		cmds->cmd = gc_strdup(current->str);
		arg_check = current;
		while (arg_check && arg_check->is_cmd)
		{
			i++;
			arg_check = arg_check->next;
		}
		cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
		i = 0;
		while (current && current->is_cmd)
		{
			cmds->args[i++] = gc_strdup(current->str);
			current = current->next;
		}
		cmds->args[i] = NULL;
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
		current = current->next;
	}
	*fullcmd = current;
}

void	sub_init_cmds(t_cmd *cmd, t_fullcmd **fullcmd, t_bool is_first)
{
	t_redir		*current_redir;
  int fd;

	cmd->is_first = is_first;

	new_cmd(cmd, fullcmd);
	if (!cmd->cmd && cmd->redir)
	{
		current_redir = cmd->redir;
		while (current_redir)
		{
			if (current_redir->type == OUT)
				fd = open(current_redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
        fd = open(current_redir->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644); // WRONLY obligatoire pour precicer que l'ecriture est autorise O_APPEN ne suffit pas
			if (fd == -1)
				error_mess(current_redir->file_name, NULL);
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
}

/* LAST
void	new_cmd(t_cmd *cmds, t_fullcmd **fullcmd)
{
	int			i;
	t_fullcmd	*current;

	i = 0;
	current = *fullcmd;
	printf("NEW_CMD\n\n");
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
		return ;
	cmds->cmd = gc_strdup(current->str);
	while (current && current->is_cmd)
	{
		i++;
		current = current->next;
	}
	cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
	i = 0;
	current = *fullcmd;
	while (current && current->is_cmd)
	{
		cmds->args[i++] = gc_strdup(current->str);
		current = current->next;
	}
	cmds->args[i] = NULL;
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
		current = current->next;
	}
	*fullcmd = current;
}
 END LAST*/



// void	new_cmd(t_cmd *cmds, t_fullcmd **fullcmd)
// {
// 	int			i;
// 	t_fullcmd	*current;
// 	t_fullcmd	*tmp;

// 	i = 0;
// 	current = *fullcmd;
// 	while (current && !current->is_cmd)
// 	{
// 		if (is_redi(current))
// 		{
// 			if (current->next && current->next->type == WORD)
// 			{
// 				add_redir(&cmds->redir, current->type, current->next->str);
// 				current = current->next;
// 			}
// 		}
// 		current = current->next;
// 	}
// 	if (!current)
// 		return ;
// 	cmds->cmd = gc_strdup(current->str);
// 	tmp = current;
// 	while (tmp && tmp->is_cmd)
// 	{
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	cmds->args = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
// 	i = 0;
// 	while (current && current->is_cmd)
// 	{
// 		cmds->args[i++] = gc_strdup(current->str);
// 		current = current->next;
// 	}
// 	cmds->args[i] = NULL;
// 	*fullcmd = current;
// }

// static t_bool	new_str(t_cmd *cmds, t_fullcmd **fullcmd)
// {
// 	int			i;
// 	t_fullcmd	*current;

// 	i = 0;
// 	current = *fullcmd;
// 	if (!cmds->cmd || !cmds->args)
// 	{
// 		return (false);
// 	}
// 	while (cmds->args[i])
// 	{
// 		printf("args[i] = %s\n\n", cmds->args[i]);
// 		i++;
// 	}
// 	cmds->str = gc_mem(MALLOC, sizeof(char *) * (i + 1), NULL);
// 	i = 0;
// 	while (cmds->args[i])
// 	{
// 		cmds->str[i] = gc_strdup(cmds->args[i]);
// 		i++;
// 	}
// 	while (current && current->type != PIPE)
// 	{
// 		if (is_redi(current))
// 		{
// 			if (current->next && current->next->type == WORD)
// 			{
// 				add_redir(&cmds->redir, current->type, current->next->str);
// 				current = current->next;
// 			}
// 		}
// 		else
// 			cmds->str[i++] = gc_strdup(current->str);
// 		current = current->next;
// 	}
// 	cmds->str[i] = NULL;
// 	*fullcmd = current;
// 	return (true);
// }

/*   last */
// void	init_single_cmd(t_cmd *cmd, t_fullcmd **fullcmd, t_bool is_first)
// {
// 	t_redir		*current_redir;

// 	cmd->is_first = is_first;
// 	new_cmd(cmd, fullcmd);
// 	if (!cmd->cmd && cmd->redir)
// 	{
// 		current_redir = cmd->redir;
// 		while (current_redir)
// 		{
// 			int fd = (current_redir->type == OUT) ?
// 				open(current_redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644) :
// 				open(current_redir->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 			if (fd == -1)
// 				error_mess(current_redir->file_name, NULL);
// 			else
// 				close(fd);
// 			current_redir = current_redir->next;
// 		}
// 	}
// }

// void	init_cmds(t_data *data)
// {
// 	t_cmd		*cmdstmp;
// 	t_fullcmd	*fullcmdtmp;
// 	t_bool		is_first;

// 	data->fd[0] = -1;
// 	data->fd[1] = -1;
// 	data->fd[2] = -1;
// 	data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
// 	init_cmd(data->cmds);
// 	cmdstmp = data->cmds;
// 	fullcmdtmp = data->token_fullcmd;
// 	is_first = true;
// 	while (fullcmdtmp)
// 	{
// 		init_single_cmd(cmdstmp, &fullcmdtmp, is_first);
// 		is_first = false;
// 		if (fullcmdtmp && fullcmdtmp->type == PIPE)
// 		{
//       printf("PIPE\n\n");
// 			fullcmdtmp = fullcmdtmp->next;
// 			cmdstmp->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
// 			init_cmd(cmdstmp->next);
// 			cmdstmp->next->prev = cmdstmp;
// 			cmdstmp = cmdstmp->next;
// 		}
// 	}
// }

/*END LAST*/

// void	init_cmds(t_data *data)
// {
// 	t_cmd		*cmdstmp;
// 	t_fullcmd	*fullcmdtmp;
// 	t_bool		is_first;

// 	data->fd[0] = -1;
// 	data->fd[1] = -1;
// 	data->fd[2] = -1;
// 	data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
// 	init_cmd(data->cmds);
// 	cmdstmp = data->cmds;
// 	fullcmdtmp = data->token_fullcmd;
// 	is_first = true;
// 	while (fullcmdtmp)
// 	{
// 		cmdstmp->is_first = is_first;
// 		is_first = false;
// 		new_cmd(cmdstmp, &fullcmdtmp);
// 		if (!cmdstmp->cmd && cmdstmp->redir)
// 		{
// 			t_redir	*current_redir = cmdstmp->redir;
// 			while (current_redir)
// 			{
// 				int fd = (current_redir->type == OUT) ?
// 					open(current_redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644) :
// 					open(current_redir->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 				if (fd == -1)
// 					error_mess("Redirection error", current_redir->file_name);
// 				else
// 					close(fd);
// 				current_redir = current_redir->next;
// 			}
// 		}

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

// Last

// void	init_cmds(t_data *data)
// {
// 	t_cmd		*cmdstmp;
// 	t_fullcmd	*fullcmdtmp;
//   t_bool    is_first;

// 	data->fd[0] = -1;
// 	data->fd[1] = -1;
// 	data->fd[2] = -1;
// 	data->cmds = gc_mem(MALLOC, sizeof(t_cmd), NULL);
// 	init_cmd(data->cmds);
// 	cmdstmp = data->cmds;
// 	fullcmdtmp = data->token_fullcmd;
//   is_first = true;
// 	while (fullcmdtmp)
// 	{
//     cmdstmp->is_first = is_first;
//     is_first = false;
// 		new_cmd(cmdstmp, &fullcmdtmp);
// 		new_str(cmdstmp, &fullcmdtmp);
//         if (fullcmdtmp && fullcmdtmp->type == PIPE)
//         {
//             fullcmdtmp = fullcmdtmp->next;
//             cmdstmp->next = gc_mem(MALLOC, sizeof(t_cmd), NULL);
//             init_cmd(cmdstmp->next);
//             cmdstmp->next->prev = cmdstmp;
//             cmdstmp = cmdstmp->next;
//         }
// 	}
// }

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
