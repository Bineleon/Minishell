/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:25:43 by neleon            #+#    #+#             */
/*   Updated: 2024/10/02 11:40:43 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*gc_free(t_garbage_co *garbage, void *ptr)
{
	while (garbage)
	{
		if (garbage->ptr == ptr)
		{
			free(garbage->ptr);
			garbage->ptr = NULL;
		}
		garbage = garbage->next;
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
		free(tmp->ptr);
		garbage = garbage->next;
		free(tmp);
	}
	free(garbage->ptr);
	free(garbage);
	return (NULL);
}

static void	*gc_malloc(t_data *data, size_t size, void *ptr)
{
	t_garbage_co	*new;

	new = malloc(sizeof(t_garbage_co));
	if (!new)
		return (perror("malloc"), gc_mem(FULL_CLEAN, 0, NULL), exit(EXIT_FAILURE), NULL);
	if (ptr)
		new->ptr = ptr;
	else
		new->ptr = malloc(size);
	if (!new->ptr)
		return (perror("malloc"), gc_mem(FULL_CLEAN, 0, NULL), exit(EXIT_FAILURE), NULL);
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
	t_data		*data;
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
