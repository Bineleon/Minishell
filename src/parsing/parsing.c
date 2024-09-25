/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:06:18 by neleon            #+#    #+#             */
/*   Updated: 2024/09/25 19:06:11 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_cmds_in_pipe(char *prompt)
{
	char	**pipe_split;

	pipe_split = ft_split(prompt, '|');
	return (pipe_split);
}

// t_token *parse_command(char *line, t_data *data)
// {
//     t_token *tokens;
//     int i = 0;
//     int j = 0;

//     tokens = gc_mem(MALLOC, sizeof(t_token) * ft_strlen(line) + 1, NULL);
//     if (!tokens)
//         return NULL;
//     while (line[i])
//     {
//         if (line[i] == '"')
//         {
//             tokens[j] = WORD;
//             handle_double_quotes(line, &i, data);
//         }
//         else if (line[i] == '\'')
//         {
//             tokens[j] = WORD;
//             i = skip_quotes(line, i, '\'');
//         }
//         else if (is_separator(line[i]))
//         {
//             if (line[i] == ' ')
//             {
//                 i++;
//                 continue;
//             }
//             tokens[j] = get_token_type(line[i]);
//         }
//         else
//             tokens[j] = WORD;
//         j++;
//         i++;
//     }
//     tokens[j] = 0;
//     return tokens;
// }
