/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:06:18 by neleon            #+#    #+#             */
/*   Updated: 2024/09/26 18:04:09 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**get_cmds_in_pipe(char *prompt)
{
	char	**pipe_split;

	pipe_split = ft_split(prompt, '|');
	return (pipe_split);
}

t_fullcmd *parse_tokens(char *line, t_data *data)
{
    t_fullcmd *head = NULL;
    t_fullcmd *current_token = NULL;
    t_fullcmd *new_token;
    int word_start;
    int i = 0;

    while (line[i])
    {
        if (is_whitespace(line[i]))
            i++;
        new_token = gc_mem(MALLOC, sizeof(t_fullcmd), NULL);
        new_token->next = NULL;
        new_token->str = NULL;

        if (current_token)
            current_token->next = new_token;
        else
            head = new_token;
        if (line[i] == '|')
        {
            new_token->type = PIPE;
            new_token->str = gc_mem(MALLOC, 2, NULL);
            new_token->str[0] = line[i];
            new_token->str[1] = '\0';
            i++;
        }
        else if (line[i] == '<')
        {
            if (line[i + 1] == '<')
            {
                new_token->type = HEREDOC;
                new_token->str = gc_mem(MALLOC, 3, NULL);
                new_token->str[0] = line[i];
                new_token->str[1] = line[i + 1];
                new_token->str[2] = '\0';
                i += 2;
            }
            else
            {
                new_token->type = IN;
                new_token->str = gc_mem(MALLOC, 2, NULL);
                new_token->str[0] = line[i];
                new_token->str[1] = '\0';
                i++;
            }
        }
        else if (line[i] == '>')
        {
            if (line[i + 1] == '>')
            {
                new_token->type = APPEND;
                new_token->str = gc_mem(MALLOC, 3, NULL);
                new_token->str[0] = line[i];
                new_token->str[1] = line[i + 1];
                new_token->str[2] = '\0';
                i += 2;
            } else
            {
                new_token->type = OUT;
                new_token->str = gc_mem(MALLOC, 2, NULL);
                new_token->str[0] = line[i];
                new_token->str[1] = '\0';
                i++;
            }
        }
        else if (line[i] == '$')
        {
            new_token->type = EXPAND;
            new_token->str = gc_mem(MALLOC, 2, NULL);
            new_token->str[0] = line[i];
            new_token->str[1] = '\0';
            i++;
        }
        else if (line[i] == '\'')
        {
            new_token->type = SQUOTE;
            new_token->str = gc_mem(MALLOC, 2, NULL);
            new_token->str[0] = line[i];
            new_token->str[1] = '\0';
            i++;
        }
        else if (line[i] == '"')
        {
            new_token->type = DQUOTE;
            new_token->str = gc_mem(MALLOC, 2, NULL);
            new_token->str[0] = line[i];
            new_token->str[1] = '\0';
            i++;
        }
        else
        {
            word_start = i;
            while (line[i] && !is_whitespace(line[i]) && !is_separator(line[i]))
                i++;
            new_token->str = gc_mem(MALLOC, i - word_start + 1, NULL);
            ft_strlcpy(new_token->str, line + word_start, i - word_start + 1);
            new_token->str[i - word_start] = '\0';
            new_token->type = WORD;
        }
        current_token = new_token;
    }
    data->token = head;
    return (head);
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
