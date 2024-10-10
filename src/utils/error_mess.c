/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 19:10:08 by elilliu           #+#    #+#             */
/*   Updated: 2024/10/10 19:42:47 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_mess(char *input, char *mess)
{
	if (input)
	{
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": ", 2);
	}
	if (!mess)
		perror(NULL);
	else
		ft_putstr_fd(mess, 2);
}
