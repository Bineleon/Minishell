/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:56:53 by neleon            #+#    #+#             */
/*   Updated: 2024/11/22 12:05:24 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	get_envp_size(char **envp)
// {
// 	int	envp_size;

// 	envp_size = 0;
// 	while (envp[envp_size])
// 		envp_size++;
// 	return (envp_size);
// }

// char	**cpy_envp(char **envp)
// {
// 	int		size;
// 	int		i;
// 	char	**envp_cpy;
//   t_data *data;

//   data = get_data();
// 	i = 0;
// 	size = get_envp_size(envp);
// 	envp_cpy = (char **)malloc(size * sizeof(char *) + 1);
// 	if (!envp_cpy)
// 		return (NULL);
// 	while (envp[i])
// 	{
// 		envp_cpy[i] = ft_strdup(envp[i]);
// 		i++;
// 	}
// 	envp_cpy[i] = NULL;
// 	return (data->envp_cpy = envp_cpy, envp_cpy);
// }

t_env   *min_node(char *key, char *value)
{
    t_env   *node;

    node = gc_mem(MALLOC, sizeof(t_env), NULL);
    node->key = gc_strdup(key);
    node->value = gc_strdup(value);
    node->equal = true;
}

t_env   *no_env()
{
    t_env   *head;

    head = min_node("PWD", getcwd(NULL, 0));
    head->next = min_node("SHLVL", "1");
    head->next->next = min_node("_", "/usr/bin/env", true);
    return (head);
}

t_env   *new_node(char *key, char *value, t_bool equal)
{
    t_env   *new_node;
    size_t  key_size;

    new_node = NULL;
    if (!equal)
		{
      new_node = gc_mem(MALLOC, sizeof(t_env), NULL);
      new_node->equal = false;
		  key_size = ft_strlen(envp[i]);
		  new_node->key = gc_mem(MALLOC, key_size + 1, NULL);
		  ft_strlcpy(new_node->key, envp[i], key_size + 1);
    }
    else
    {
      new_node = gc_mem(MALLOC, sizeof(t_env), NULL);
      key_size = equal - envp[i];
      new_node->key = gc_mem(MALLOC, key_size + 1, NULL);
      ft_strlcpy(new_node->key, envp[i], key_size + 1);
      new_node->value = gc_strdup(equal + 1);
      new_node->next = NULL;
    }
}

t_env   *env_cpy(char **envp)
{
    t_env	*head;
    t_env	*current;
    t_env	*new_node;
    size_t	key_size;
    char	*equal;
    int		i;

    i = 0;
    equal = NULL;
    key_size = 0;
    current = NULL;
    new_node = NULL;
    head = NULL;
    if (!envp || !envp[0])
        return (no_env());
    while (envp[i])
    {
        equal = ft_strchr(envp[i], '=');
        if (!equal)
        {
            new_node = gc_mem(MALLOC, sizeof(t_env), NULL);
            new_node->equal = false;
            key_size = ft_strlen(envp[i]);
            new_node->key = gc_mem(MALLOC, key_size + 1, NULL);
            ft_strlcpy(new_node->key, envp[i], key_size + 1);
        }
        else
        {
            new_node = gc_mem(MALLOC, sizeof(t_env), NULL);
            key_size = equal - envp[i];
            new_node->key = gc_mem(MALLOC, key_size + 1, NULL);
            ft_strlcpy(new_node->key, envp[i], key_size + 1);
            new_node->value = gc_strdup(equal + 1);
            new_node->next = NULL;
        }
        if (current)
            current->next = new_node;
        else
            head = new_node;
        current = new_node;
        i++;
    }
    return (head);
}
