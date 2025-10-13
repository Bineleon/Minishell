/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:11:52 by neleon            #+#    #+#             */
/*   Updated: 2024/12/12 16:37:07 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_fullcmd	*create_token(t_fullcmd **current_token, t_fullcmd **head)
{
	t_fullcmd	*new_token;

	new_token = gc_mem(MALLOC, sizeof(t_fullcmd), NULL);
	new_token->concat_next = false;
	new_token->is_cmd = false;
	new_token->next = NULL;
	if (*current_token)
		(*current_token)->next = new_token;
	else
		*head = new_token;
	return (new_token);
}

int	to_handle_pipe(char *line, int i, t_fullcmd *token)
{
	token->type = PIPE;
	token->str = gc_mem(MALLOC, 2, NULL);
	token->str[0] = line[i];
	token->str[1] = '\0';
	return (i + 1);
}
