/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:06:18 by neleon            #+#    #+#             */
/*   Updated: 2024/09/13 18:10:31 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_cmds_in_pipe(char *prompt)
{
	char	**pipe_split;

	pipe_split = ft_split(prompt, '|');
	return (pipe_split);
}

// void	get_args_count(t_data *data, char **cmds)
// {
// 	int count;
	
// 	count = 0;
// 	while (cmds[i])
// 		count++;
// 	data->cmds_count = count;
// }

// void	add_cmd_to_lst(char **cmds, t_lst *lst, t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	lst->cmd->args = malloc(data->cmds_count * sizeof(char *) + 1);
// 	while (cmds[i])
// 	{
// 		lst->cmd->args = cmds[i];
// 		lst = lst->next;
// 	}
	
// }