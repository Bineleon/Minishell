/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 18:58:53 by neleon            #+#    #+#             */
/*   Updated: 2024/12/13 20:00:38 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*gc_free(t_garbage_co *garbage, void *ptr)
{
	t_garbage_co *current;

	current = garbage;
	while (current)
	{
		if (current->ptr == ptr)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		current = current->next;
	}
	return (NULL);
}

static void	*gc_full_clean(t_garbage_co *garbage)
{
	t_garbage_co	*tmp;

	tmp = garbage;
	while (garbage->next)
	{
		tmp = garbage;
		if (tmp->ptr)
		{
			free(tmp->ptr);
			tmp->ptr = NULL;
		}
		garbage = garbage->next;
		free(tmp);
	}
	if (garbage->ptr)
		free(garbage->ptr);
	free(garbage);
	return (NULL);
}

static void	*gc_malloc(t_data *data, size_t size, void *ptr)
{
	t_garbage_co	*new;

	new = ft_calloc(sizeof(t_garbage_co), 1);
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
	if (data->garbage)
	{
		new->next = data->garbage;
		data->garbage = new;
	}
	else if (data->garbage == NULL)
	{
		new->next = NULL;
		data->garbage = new;
	}
	return (new->ptr);
}

void	*gc_mem(t_mem type, size_t size, void *ptr)
{
	t_data			*data;
	t_garbage_co	*garb;

	data = get_data();
	garb = data->garbage;
	if (type == MALLOC)
		return (gc_malloc(data, size, ptr));
	else if (type == FULL_CLEAN && garb)
		return (gc_full_clean(garb));
	else if (type == FREE && garb)
		return (gc_free(garb, ptr));
	return (NULL);
}
