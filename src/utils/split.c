/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:33 by neleon            #+#    #+#             */
/*   Updated: 2024/09/25 22:17:16 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_args(char *line)
{
    int i;
    int arg_count;

    i = 0;
    arg_count = 0;
    while (line[i])
    {
        if (is_whitespace(line[i]))
            i++;
        else if (line[i] == DQUOTE || line[i] == SQUOTE)
        {
            i = skip_quotes(line, i, line[i]);
            arg_count++;
        }
        else
        {
            while (line[i] && !is_whitespace(line[i]) && line[i] != DQUOTE && line[i] != SQUOTE)
                i++;
            arg_count++;
        }
    }
    return arg_count;
}

int skip_quotes(char *line, int i, char quote)
{
    while (line[i] && line[i] != quote)
        i++;
    return (i + 1);
}

char **allocate_args(int arg_count)
{
    char **args;

    args = gc_mem(MALLOC, sizeof(char *) * arg_count + 1, NULL);
    if (!args)
    {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    return (args);
}

int skip_spaces(char *line, int i)
{
    while (is_whitespace(line[i]))
        i++;
    return i;
}

int in_quote_arg(char *line, char **args, int i, int *j)
{
    char quote;
    int start;
    int len;

    quote = line[i];
    start = i;
    i++;
    i = skip_quotes(line, i, quote);
    len = i - start;
    args[*j] = gc_mem(MALLOC, len + 1, NULL);
    ft_strlcpy(args[*j], &line[start], len + 1);
    args[*j][len] = '\0';
    (*j)++;
    return (i);
}

int not_quoted_arg(char *line, char **args, int i, int *j)
{
    int start;
    int len;

    start = i;
    while (line[i] && line[i] != SPACE && line[i] != DQUOTE && line[i] != SQUOTE)
        i++;
    len = i - start;
    args[*j] = gc_mem(MALLOC, len + 1, NULL);
    ft_strlcpy(args[*j], &line[start], len + 1);
    args[*j][len] = '\0';
    (*j)++;
    return (i);
}

void extract_args(char *line, char **args)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (line[i])
    {
        i = skip_spaces(line, i);
        if (line[i] == DQUOTE || line[i] == SQUOTE)
            i = in_quote_arg(line, args, i, &j);
        else if (line[i])
            i = not_quoted_arg(line, args, i, &j);
    }
    args[j] = NULL;
}

char **split_args(char *line)
{
    int arg_count;
    char **args;

    arg_count = count_args(line);
    args = allocate_args(arg_count);
    extract_args(line, args);
    return args;
}

// int main(void)
// {
//     char *line = "echo           \"Hello      you\" > 'output.txt'            ";

//     char **args = split_args(line);

//     int i = 0;
//     printf("Arguments:\n");
//     while (args[i] != NULL)
//     {
//         printf("args[%d]: %s\n", i, args[i]);
//         i++;
//     }
//     i = 0;
//     while (args[i] != NULL)
//     {
//         free(args[i]);
//         i++;
//     }
//     free(args);

//     return 0;
// }
