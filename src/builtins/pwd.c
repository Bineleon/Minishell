/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:39:51 by neleon            #+#    #+#             */
/*   Updated: 2024/11/23 13:12:26 by bineleon         ###   ########.fr       */
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

void	ft_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX))
		printf("%s\n", buf);
	else
		perror("getcwd(): ");
}
