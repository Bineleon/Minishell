/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:26:22 by neleon            #+#    #+#             */
/*   Updated: 2024/12/14 01:24:14 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*gc_free_env(t_garbage_env *garbage, void *ptr)
{
	t_garbage_env	*prev;
	t_garbage_env	*current;

	current = garbage;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			free(current->ptr);
			current->ptr = NULL;
		}
		prev = current;
		current = current->next;
	}
	return (NULL);
}

static void	*gc_full_clean_env(t_garbage_env *garbage)
{
	t_garbage_env	*tmp;

	tmp = garbage;
	while (garbage->next)
	{
		tmp = garbage;
		if (tmp->ptr)
			free(tmp->ptr);
		garbage = garbage->next;
		free(tmp);
	}
	if (garbage->ptr)
		free(garbage->ptr);
	free(garbage);
	return (NULL);
}

static void	*gc_malloc_env(t_data *data, size_t size, void *ptr)
{
	t_garbage_env	*new;

	new = ft_calloc(sizeof(t_garbage_env), 1);
	if (!new)
		return (perror("malloc"), gc_mem(FULL_CLEAN, 0, NULL),
			exit(EXIT_FAILURE), NULL);
	if (ptr)
		new->ptr = ptr;
	else
		new->ptr = ft_calloc(1, size);
	if (!new->ptr)
		return (perror("malloc"), gc_mem(FULL_CLEAN, 0, NULL),
			exit(EXIT_FAILURE), NULL);
	if (data->garbage_env)
	{
		new->next = data->garbage_env;
		data->garbage_env = new;
	}
	else if (data->garbage_env == NULL)
	{
		new->next = NULL;
		data->garbage_env = new;
	}
	return (new->ptr);
}

void	*gc_mem_env(t_mem type, size_t size, void *ptr)
{
	t_data			*data;
	t_garbage_env	*garb;

	data = get_data();
	garb = data->garbage_env;
	if (type == MALLOC)
		return (gc_malloc_env(data, size, ptr));
	else if (type == FULL_CLEAN && garb)
		return (gc_full_clean_env(garb));
	else if (type == FREE && garb)
		return (gc_free_env(garb, ptr));
	return (NULL);
}
