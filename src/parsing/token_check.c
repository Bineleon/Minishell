/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:01 by neleon            #+#    #+#             */
/*   Updated: 2024/09/26 15:59:51 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool is_separator(char c)
{
    if (c == '|' || c == '<' || c == '>' || c == '$')
      return (true);
    return (false);
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
