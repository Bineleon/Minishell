/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 20:47:22 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 23:24:17 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	full_clean_hd(t_data *data)
{
	clean_heredoc(data);
	close(data->cmds->fd_redir[0]);
	close(data->cmds->fd_redir[1]);
	error_mess("warning", "heredoc delimited by EOF\n");
}

void	end_hd(t_data *data, t_cmd *cmd, int stdi, char **prompt)
{
	ft_putstr_fd(data->heredoc->fullprompt, data->heredoc->fd[1]);
	dup2(data->heredoc->fd[0], cmd->fd_redir[0]);
	clean_heredoc(data);
	free(*prompt);
	close(stdi);
}

int	sub_hd(t_data *data, char **prompt)
{
	data->sig = 0;
	new_heredoc(data);
	data->heredoc->in_process = true;
	handle_signals();
	if (pipe(data->heredoc->fd) == -1)
		return (clean_heredoc(data), error_mess(NULL, NULL), 0);
	*prompt = NULL;
	return (1);
}

void	join_heredoc(t_data *data, char **prompt)
{
	data->heredoc->fullprompt = gc_strjoin(data->heredoc->fullprompt, *prompt);
	gc_mem(FREE, (size_t) NULL, *prompt);
	data->heredoc->fullprompt = gc_strjoin(data->heredoc->fullprompt, "\n");
}

void	heredoc(t_data *data, t_cmd *cmd, t_redir *current_redir)
{
	char	*prompt;
	int		stdi;

	save_stdin(&stdi);
	if (!sub_hd(data, &prompt))
		return ;
	while (data->sig != 130)
	{
		signal(SIGQUIT, SIG_IGN);
		prompt = readline("> ");
		if (!prompt && data->sig == 130)
			return (restore_stdin(&stdi));
		else if (!prompt && data->sig != 130)
		{
			error_mess("warning", "heredoc delimited by EOF\n");
			break ;
		}
		if (is_delim(current_redir, prompt) == 1)
		{
			gc_mem(FREE, (size_t) NULL, prompt);
			break ;
		}
		join_heredoc(data, &prompt);
	}
	end_hd(data, cmd, stdi, &prompt);
}
