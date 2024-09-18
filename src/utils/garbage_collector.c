/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:25:43 by neleon            #+#    #+#             */
/*   Updated: 2024/09/18 18:05:17 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*gc_mem(t_garbage_co *mem_lst, t_mem type, size_t size, void *ptr)
{
	void	*new_ptr;
	void	*new_node;
	
	if (type == MALLOC)
	{
		new_ptr = malloc(size);
		if (!new_ptr)
		{
			perror("malloc");
			return (NULL);
		}
		new_node->ptr = new_ptr;
		if (!mem_lst)
			mem_lst = malloc(sizeof(t_garbage_co *) + 1);
		else
		{
			mem_lst->next = new_node->ptr;
			new_node->next = NULL;
		}
	}
	else if (type == FREE)
	// TODO
}
