/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 11:49:57 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/12 20:36:35 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_delim(t_redir *current_redir, char *prompt)
{
	if (ft_strlen(current_redir->file_name) == ft_strlen(prompt)
		&& ft_strncmp(current_redir->file_name, prompt,
			ft_strlen(current_redir->file_name)) == 0)
		return (1);
	return (0);
}

int	new_input_fd(t_data *data, t_redir *current_redir, int *fd)
{
	if (current_redir->type == IN)
	{
		(*fd) = open(current_redir->file_name, O_RDONLY);
		if (*fd == -1)
		{
			error_mess(current_redir->file_name, NULL);
			data->exit_status = 1;
			return (0);
		}
	}
	else if (current_redir->type == HEREDOC)
	{
		heredoc(data, current_redir);
		if (*fd > 0)
			close(*fd);
		(*fd) = 0;
	}
	return (1);
}
