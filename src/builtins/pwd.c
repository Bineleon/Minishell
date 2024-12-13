/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:39:51 by neleon            #+#    #+#             */
/*   Updated: 2024/12/13 13:21:08 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*search_in_env(t_data *data, char *str)
// {
// 	t_env	*env;

// 	env = data->envp_cpy;
// 	while (env)
// 	{
// 		if (ft_strncmp(str, env->key, INT_MAX) == 0)
// 			return (env->value);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

void	ft_pwd(t_data *data)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
  {
    ft_putstr_fd(buf, data->fd_);
    ft_putstr_fd("\n", data->fd_);
    data->exit_status = 0;
  }
	else
	{
		perror("getcwd(): ");
		data->exit_status = 1;
	}
}
