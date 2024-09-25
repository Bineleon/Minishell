/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:01 by neleon            #+#    #+#             */
/*   Updated: 2024/09/25 21:34:05 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_separator(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '$' || c == ' ');
}

t_token get_token_type(char c)
{
	if (c == '|')
		return PIPE;
	if (c == '<')
		return IN;
	if (c == '>')
		return OUT;
  if (c == ' ')
		return SPC;
	if (c == '$')
		return EXPAND;
	return WORD;
}
