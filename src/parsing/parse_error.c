/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:06:38 by neleon            #+#    #+#             */
/*   Updated: 2024/10/11 14:09:45 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool check_open_quotes(char *line)
{
    t_bool dq;
    t_bool sq;
    int i;

    i = 0;
    dq = false;
    sq = false;
    while (line[i])
    {
        if (line[i] == SQUOTE && !dq)
            sq = !sq;
        else if (line[i] == DQUOTE && !sq)
            dq = !dq;
        i++;
    }
    if (dq || sq)
    {
        ft_putstr_fd("Error: Open quote\n", 2);
        return (true);
    }
    return (false);
}

t_bool pipe_errors(t_fullcmd *tokens)
{
    t_fullcmd *current;

    current  = tokens;
    if (current && current->type == PIPE)
    {
        ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
        return (true);
    }
    while (current)
    {
        if (current->type == PIPE && (current->next->type == PIPE || current->next->type != WORD
            || !current->next))
        {
            ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
            return (true);
        }
        current = current->next;
    }
    return (false);
}

t_bool  sub_redirect_errors(t_fullcmd *tokens)
{
      if (!tokens->next || tokens->next->type != WORD)
      {
        if (tokens->type == IN || tokens->type == OUT)
            ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
        if (tokens->type == APPEND)
            ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
        if (tokens->type == HEREDOC)
            ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
        return (true);
      }
      return (false);
}

t_bool redirect_errors(t_fullcmd *tokens)
{
    t_fullcmd *current;

    current = tokens;
    if (current && (current->type == IN || current->type == OUT
        || current->type == APPEND || current->type == HEREDOC)
        && !current->next )
    {
        ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
        return (true);
    }
    while (current)
    {
        sub_redirect_errors(current);
        current = current->next;
    }
    return (false);
}

t_bool expand_errors(t_fullcmd *tokens)
{
    t_fullcmd *current;

    current = tokens;
    while (current)
    {
        if ((current->type == EXPAND)
            && (!current->next || current->next->type == EXPAND))
        {
            ft_putstr_fd("Error: Expand\n", 2);
            return (true);
        }
        current = current->next;
    }

    return (false);
}

t_bool  check_errors(t_fullcmd *tokens)
{
  if (pipe_errors(tokens) || redirect_errors(tokens))
    return (true);
  return (false);
}
