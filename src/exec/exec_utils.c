/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu@student.42.fr <elilliu>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:26:55 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/21 23:32:20 by elilliu@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join(char *path, char *cmd)
{
	char	*tmp;
	char	*str;
	
	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, cmd);
	if (!str)
		return (free(tmp), (NULL));
	free(tmp);
	return (str);
}
