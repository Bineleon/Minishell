/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:26:55 by elilliu           #+#    #+#             */
/*   Updated: 2024/12/15 02:21:11 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*joinequal(char *key, char *value)
{
	char	*tmp;
	char	*str;

	tmp = gc_strjoin(key, "=");
	str = gc_strjoin(tmp, value);
	if (!str)
		return (gc_mem(FREE, 0, tmp), NULL);
	gc_mem(FREE, 0, tmp);
	return (str);
}

char	*join(char *path, char *cmd)
{
	char	*tmp;
	char	*str;

	tmp = gc_strjoin(path, "/");
	str = gc_strjoin(tmp, cmd);
	if (!str)
		return (gc_mem(FREE, 0, tmp), (NULL));
	gc_mem(FREE, 0, tmp);
	return (str);
}
