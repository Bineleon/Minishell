/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:10:08 by elilliu           #+#    #+#             */
/*   Updated: 2024/11/27 19:21:12 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_mess(char *input, char *mess)
{
	if (input)
	{
    ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": ", 2);
	}
	if (!mess)
		perror(NULL);
	else
		ft_putstr_fd(mess, 2);
}

void	error_cmd(char *cmd)
{
  ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : command not found\n", 2);
}

void    error_syntax(char *str)
{
    ft_putstr_fd("syntax error near unexpected token ", 2);
    ft_putstr_fd(str, 2);
}
