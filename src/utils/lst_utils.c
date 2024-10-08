/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:36:41 by bineleon          #+#    #+#             */
/*   Updated: 2024/09/19 20:55:09 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// t_lst	*ft_lstnew(t_cmd *cmd)
// {
// 	t_lst	*new;

// 	new = (t_lst *)malloc(sizeof(t_lst));
// 	if (!new)
// 		return (NULL);
// 	new->cmd = cmd;
// 	new->next = NULL;
// 	return (new);
// }

// void	ft_lstadd_back(t_lst **lst, t_lst *new)
// {
// 	t_lst	*tmp;

// 	if (!(*lst) && new)
// 		*lst = new;
// 	else if (*lst && new)
// 	{
// 		tmp = *lst;
// 		while (tmp->next)
// 			tmp = tmp->next;
// 		tmp->next = new;
// 	}
// }

// void ft_print_lst(t_lst *cmd)
// {
//     t_lst *current = cmd;
//     while (current)
//     {
//         if (current->cmd && current->cmd[0])
//         {
//             printf("Cmd: %s\n", current->cmd[0]);
//         }
//         current = current->next;
//     }
// }
