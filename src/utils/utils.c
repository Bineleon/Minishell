/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:22 by neleon            #+#    #+#             */
/*   Updated: 2024/09/27 17:53:32 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_whitespace(char c)
{
	if ((c == 32 || (c >= 9 && c <= 13)))
		return (true);
	return (false);
}

t_bool  isquote(char c)
{
  if (c == SQUOTE || c == DQUOTE)
      return(true);
  return (false);
}

t_bool is_separator(char c)
{
    if (c == '|' || c == '<' || c == '>' || c == '$')
      return (true);
    return (false);
}
