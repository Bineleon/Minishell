/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:56:53 by neleon            #+#    #+#             */
/*   Updated: 2024/11/27 14:48:40 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*min_node(char *key, char *value)
{
	t_env	*node;

	node = gc_mem(MALLOC, sizeof(t_env), NULL);
	node->key = gc_strdup(key);
	node->value = gc_strdup(value);
	node->equal = true;
	return (node);
}

t_env	*no_env(void)
{
	t_env	*head;
  t_data  *data;
	char	buf[PATH_MAX];

  data = get_data();
	if (!getcwd(buf, PATH_MAX))
	{
		perror("getcwd(): ");
    data->exit_status = 1;
		return (NULL);
	}
	head = min_node("PWD", buf);
	head->next = min_node("SHLVL", "1");
	head->next->next = min_node("_", "/usr/bin/env");
	return (head);
}

t_env	*new_env_node(char *line, char *equal)
{
	t_env	*new_node;
	size_t	key_size;

	new_node = NULL;
	if (!equal)
		key_size = ft_strlen(line);
	else
		key_size = equal - line;
	new_node = gc_mem(MALLOC, sizeof(t_env), NULL);
	new_node->key = gc_mem(MALLOC, key_size + 1, NULL);
	ft_strlcpy(new_node->key, line, key_size + 1);
	if (equal)
	{
		new_node->value = gc_strdup(equal + 1);
		new_node->equal = true;
	}
	else
		new_node->equal = false;
	new_node->next = NULL;
	return (new_node);
}

t_env	*env_cpy(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	char	*equal;
	int		i;

	i = 0;
	equal = NULL;
	current = NULL;
	new_node = NULL;
	head = NULL;
	if (!envp || !envp[0])
		return (no_env());
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		new_node = new_env_node(envp[i], equal);
		if (current)
			current->next = new_node;
		else
			head = new_node;
		current = new_node;
		i++;
	}
	return (head);
}
