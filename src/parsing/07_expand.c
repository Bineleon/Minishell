/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:14:34 by neleon            #+#    #+#             */
/*   Updated: 2024/12/12 16:14:36 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *alloc_var_name(char *str, int start, int end)
{
    char *var_name;
    int len;

    len = end - start;
    var_name = gc_mem(MALLOC, len + 1, NULL);
    ft_strlcpy(var_name, &str[start], len + 1);
    return (var_name);
}

void sub_expand(t_fullcmd *token, char *result)
{
    gc_mem(FREE, 0, token->str);
    token->str = result;
    token->type = WORD;
}

int var_expand(char *str, int i, char **result, t_env *env_list)
{
    int start;
    char *exit_status;
    char *var_name;
    char *env_value;
    t_data  *data;

    data = get_data();
    if (str[i + 1] == '?')
    {
        exit_status = gc_itoa(data->exit_status);
        *result = gc_strjoin(*result, exit_status);
        gc_mem(FREE, 0, exit_status);
        return (i + 2);
    }
    start = ++i;
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    var_name = alloc_var_name(str, start, i);
    env_value = get_env_value(var_name, env_list);
    gc_mem(FREE, 0, var_name);
    if (env_value)
        *result = gc_strjoin(*result, env_value);
    return (i);
}

void handle_expand(t_fullcmd *token, t_env *env_list)
{
    char *result;
    int i;

    result = init_result();
    i = 0;

    while (token->str[i])
    {
        if (token->str[i] == '$')
            i = var_expand(token->str, i, &result, env_list);
        else
            i = process_word(token->str, i, &result);
    }
    sub_expand(token, result);
}


// void handle_expand(t_fullcmd *token, t_env *env_list)
// {
//     char *result;
//     int i;

//     result = init_result();
//     i = 0;

//     while (token->str[i])
//     {
//         if (token->str[i] == '$')
//         {
//             if (token->str[i + 1] == '?')
//             {
//                 char *exit_status = gc_itoa(get_data()->exit_status);
//                 result = gc_strjoin(result, exit_status);
//                 gc_mem(FREE, 0, exit_status);
//                 i += 2;
//             }
//             else
//             {
//                 int start = ++i;
//                 while (token->str[i] && (ft_isalnum(token->str[i]) || token->str[i] == '_'))
//                     i++;
//                 char *var_name = gc_mem(MALLOC, i - start + 1, NULL);
//                 ft_strlcpy(var_name, &token->str[start], i - start + 1);
//                 char *env_value = get_env_value(var_name, env_list);
//                 gc_mem(FREE, 0, var_name);
//                 if (env_value)
//                     result = gc_strjoin(result, env_value);
//             }
//         }
//         else
//         {
//             i = process_word(token->str, i, &result);
//         }
//     }
//     gc_mem(FREE, 0, token->str);
//     token->str = result;
//     token->type = WORD;
// }
