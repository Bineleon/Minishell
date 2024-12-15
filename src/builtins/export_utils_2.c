/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 01:07:48 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 15:23:27 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	**lst_to_arr(t_env *env)
{
	t_env	**arr;
	t_env	*curr;
	size_t	env_size;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	env_size = get_env_size(env);
	arr = gc_mem_env(MALLOC, (env_size * sizeof(t_env)) + 1, NULL);
	curr = env;
	while (curr)
	{
		arr[i] = gc_mem_env(MALLOC, sizeof(t_env), NULL);
		init_env(arr[i]);
		arr[i]->key = gc_strdup_env(curr->key);
		if (curr->value)
			arr[i]->value = gc_strdup_env(curr->value);
		arr[i]->equal = curr->equal;
		arr[i]->next = NULL;
		curr = curr->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void print_export(t_env **arr)
{
    int i;
    t_data *data;

    i = 0;
    data = get_data();
    if (!arr)
        return;
    while (arr[i])
    {
        if (arr[i]->value)
        {
            ft_putstr_fd("export ", data->fd_);
            ft_putstr_fd(arr[i]->key, data->fd_);
            ft_putstr_fd("=\"", data->fd_);
            ft_putstr_fd(arr[i]->value, data->fd_);
            ft_putstr_fd("\"\n", data->fd_);
        }
        else if (arr[i]->equal == false)
        {
            ft_putstr_fd("export ", data->fd_);
            ft_putstr_fd(arr[i]->key, data->fd_);
            ft_putstr_fd("\n", data->fd_);
        }
        else if (arr[i]->equal && !arr[i]->value)
        {
            ft_putstr_fd("export ", data->fd_);
            ft_putstr_fd(arr[i]->key, data->fd_);
            ft_putstr_fd("=\"\"\n", data->fd_);
        }
        i++;
    }
}

// void	print_export(t_env **arr)
// {
// 	int	i;
//   t_data *data;

// 	i = 0;
//   data = get_data();
// 	if (!arr)
// 		return ;
// 	while (arr[i])
// 	{
// 		if (arr[i]->value)
// 			printf("export %s=\"%s\"\n", arr[i]->key, arr[i]->value);
// 		else if (arr[i]->equal == false)
// 			printf("export %s\n", arr[i]->key);
// 		else if (arr[i]->equal && !arr[i]->value)
// 			printf("export %s=\"\"\n", arr[i]->key);
// 		i++;
// 	}
// }
