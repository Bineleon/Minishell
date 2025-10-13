/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:57:31 by neleon            #+#    #+#             */
/*   Updated: 2024/10/25 18:58:07 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	get_token_type(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
		return (IN);
	if (c == '>')
		return (OUT);
	if (c == ' ')
		return (SPC);
	if (c == '$')
		return (EXPAND);
	return (WORD);
}
