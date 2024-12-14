/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:46:29 by neleon            #+#    #+#             */
/*   Updated: 2024/12/14 01:12:28 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_env(t_env **env, char *key, char *value, t_bool equal)
{
	t_env	*curr;
	t_env	*new_node;

	curr = *env;
	new_node = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			gc_mem_env(FREE, 0, curr->value);
			curr->value = gc_strdup_env(value);
			return ;
		}
		curr = curr->next;
	}
	new_node = gc_mem_env(MALLOC, sizeof(t_env), NULL);
	init_env(new_node);
	new_node->key = gc_strdup_env(key);
	if (value)
		new_node->value = gc_strdup_env(value);
	if (!equal)
		new_node->equal = false;
	new_node->next = *env;
	*env = new_node;
}

void	handle_no_equal(t_data *data, char *key)
{
	if (!is_valid_key(key))
	{
		error_mess("export", key);
		ft_putstr_fd(" : not a valid identifier\n", 2);
		data->exit_status = 1;
	}
	else
	{
		update_env(&data->envp_cpy, key, NULL, false);
		data->exit_status = 0;
	}
}

void	handle_with_equal(t_data *data, char *arg)
{
	char	*equal;
	char	*key;
	char	*value;

	equal = ft_strchr(arg, '=');
	if (equal)
	{
		*equal = '\0';
		key = arg;
		value = equal + 1;
		if (!is_valid_key(key))
		{
			error_export(key);
			data->exit_status = 1;
		}
		else
		{
			update_env(&data->envp_cpy, key, value, true);
			data->exit_status = 0;
		}
		*equal = '=';
	}
}

void	sub_export(t_data *data, t_cmd *cmds)
{
	int		i;
	char	*arg;
	char	*equal;

	i = 1;
	while (cmds->args[i])
	{
		arg = cmds->args[i];
		equal = ft_strchr(arg, '=');
		if (equal)
			handle_with_equal(data, arg);
		else
			handle_no_equal(data, arg);
		i++;
	}
}

void	ft_export(t_cmd *cmds)
{
	t_env	**sorted_env;
	t_data	*data;

	data = get_data();
	sorted_env = lst_to_arr(data->envp_cpy);
	sort_env(sorted_env);
	if (!cmds->args[1])
		print_export(sorted_env);
	sub_export(data, cmds);
}
