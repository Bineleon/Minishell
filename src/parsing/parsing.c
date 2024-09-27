/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:06:18 by neleon            #+#    #+#             */
/*   Updated: 2024/09/27 17:56:07 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_cmds_in_pipe(char *prompt)
{
	char	**pipe_split;

	pipe_split = ft_split(prompt, '|');
	return (pipe_split);
}
