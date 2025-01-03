/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:46:58 by neleon            #+#    #+#             */
/*   Updated: 2024/12/07 17:41:59 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*is_in_env(t_data *data, t_env **prev, char *key, t_bool *is_head)
{
	t_env	*curr;
	int		len;

	if (!data->envp_cpy)
		return (NULL);
	curr = data->envp_cpy;
	len = ft_strlen(key);
	if (!ft_strncmp(curr->key, key, len) && curr->key[ft_strlen(key)] == '\0')
	{
		*is_head = true;
		return (curr);
	}
	while (curr)
	{
		len = ft_strlen(key);
		if (!ft_strncmp(curr->key, key, len)
			&& curr->key[ft_strlen(key)] == '\0')
			return (curr);
		*prev = curr;
		curr = curr->next;
	}
	return (NULL);
}

void	rm_var(t_data *data, char *key)
{
	t_env	*tmp;
	t_env	*prev;
	t_bool	is_head;

	is_head = false;
	prev = NULL;
	tmp = is_in_env(data, &prev, key, &is_head);
	if (tmp)
	{
		if (is_head)
		{
			data->envp_cpy = data->envp_cpy->next;
			free_env_node(tmp);
		}
		else
		{
			prev->next = tmp->next;
			free_env_node(tmp);
		}
		data->exit_status = 0;
		return ;
	}
	data->exit_status = 1;
}

void	ft_unset(t_cmd *cmds)
{
	int		i;
	char	*key;
	t_data	*data;

	i = 1;
	key = NULL;
	data = get_data();
	if (!cmds->args[i])
	{
		error_mess("unset", "missing argument(s)\n");
		data->exit_status = 1;
		return ;
	}
	while (cmds->args[i])
	{
		key = cmds->args[i];
		if (!is_valid_key(key))
		{
			error_mess("unset", key);
			ft_putstr_fd(": not a valid identifier\n", 2);
			data->exit_status = 1;
			i++;
			continue ;
		}
		rm_var(data, key);
		i++;
	}
}
