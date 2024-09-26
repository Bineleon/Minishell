/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 17:06:38 by neleon            #+#    #+#             */
/*   Updated: 2024/09/26 15:41:41 by bineleon         ###   ########.fr       */
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
        return true;
    }
    return false;
}
