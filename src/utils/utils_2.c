/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 00:32:50 by neleon            #+#    #+#             */
/*   Updated: 2024/12/15 16:23:14 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	check_open_quotes(char *line)
{
	t_bool	dq;
	t_bool	sq;
	t_data	*data;
	int		i;

	i = 0;
	dq = false;
	sq = false;
	data = get_data();
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
		data->exit_status = 1;
		return (true);
	}
	return (false);
}

long long int	ft_atol(const char *nptr)
{
	int		i;
	long	sign;
	long	res;

	i = 0;
	res = 0;
	sign = 1;
	while ((nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while ((nptr[i] >= '0' && nptr[i] <= '9'))
	{
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return (res * sign);
}

t_bool	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (true);
}
