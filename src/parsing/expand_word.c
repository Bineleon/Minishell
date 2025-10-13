/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:12:32 by neleon            #+#    #+#             */
/*   Updated: 2024/12/12 16:12:35 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	process_word(char *str, int i, char **result)
{
	int		start;
	char	*text;

	start = i;
	while (str[i] && str[i] != '$')
		i++;
	text = gc_mem(MALLOC, i - start + 1, NULL);
	ft_strlcpy(text, str + start, i - start + 1);
	*result = gc_strjoin(*result, text);
	gc_mem(FREE, 0, text);
	return (i);
}
