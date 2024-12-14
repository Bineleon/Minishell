/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:22 by neleon            #+#    #+#             */
/*   Updated: 2024/12/14 00:40:46 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_whitespace(char c)
{
	if ((c == 32 || (c >= 9 && c <= 13)))
		return (true);
	return (false);
}

t_bool	isquote(char c)
{
	if (c == SQUOTE || c == DQUOTE)
		return (true);
	return (false);
}

t_bool	is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

void	free_env_node(t_env *node)
{
	if (node->key)
		gc_mem_env(FREE, 0, node->key);
	if (node->value)
		gc_mem_env(FREE, 0, node->value);
	node = NULL;
	gc_mem_env(FREE, 0, node);
}

void	ciao(int exit_status)
{
	printf(MAGENTA);
	printf("\e[4mCIAO BABY!\e[0m\n");
	printf(RESET);
	gc_mem(FULL_CLEAN, 0, NULL);
	gc_mem_env(FULL_CLEAN, 0, NULL);
	exit(exit_status);
}
