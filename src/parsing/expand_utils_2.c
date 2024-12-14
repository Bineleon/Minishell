/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:45:42 by neleon            #+#    #+#             */
/*   Updated: 2024/12/14 00:50:44 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*init_result(void)
{
	char	*result;

	result = gc_mem(MALLOC, 1, NULL);
	result[0] = '\0';
	return (result);
}

void	init_var(int *i, int *j, char **tmp, t_fullcmd *token)
{
	*i = 1;
	*j = 0;
	*tmp = gc_mem(MALLOC, ft_strlen(token->str) + 1, NULL);
}

char	*extract_var_name(char *str, int start, int end)
{
	char	*var_name;

	var_name = gc_mem(MALLOC, end - start, NULL);
	ft_strlcpy(var_name, str + start + 1, end - start);
	return (var_name);
}
