/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elilliu <elilliu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:34:22 by neleon            #+#    #+#             */
/*   Updated: 2024/12/10 16:40:48 by elilliu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_bool	is_whitespace(char c)
{
	if ((c == 32 || (c >= 9 && c <= 13)))
		return (true);
	return (false);
}

t_bool	isquote(char c)
{
	if (c == SQUOTE || c == DQUOTE)
		return (true);
	return (false);
}

t_bool	is_separator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (true);
	return (false);
}

void	free_env_node(t_env *node)
{
	if (node->key)
		gc_mem(FREE, 0, node->key);
	if (node->value)
		gc_mem(FREE, 0, node->value);
	node = NULL;
	gc_mem(FREE, 0, node);
}

char	*gc_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len_s1;
	size_t	len_s2;

	if (!s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	join = gc_mem(MALLOC, (len_s1 + len_s2 + 1) * sizeof(char), NULL);
	if (!join)
		return (NULL);
	ft_strlcpy(join, s1, (len_s1 + 1));
	ft_strlcat(join, s2, len_s1 + len_s2 + 1);
	return (join);
}

char	*gc_strdup(const char *s1)
{
	size_t	len;
	char	*str;
	int		i;

	i = 0;
	len = ft_strlen(s1);
	str = gc_mem(MALLOC, (len + 1) * sizeof(char), NULL);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static long	ft_nb_size(long nb)
{
	long	size;
	long	sign;

	size = 0;
	sign = 1;
	if (nb < 0)
	{
		sign = -sign;
		nb = -nb;
		size++;
	}
	else if (nb == 0)
		return (1);
	while (nb != 0)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

static void	ft_nbr_to_str(long nb, char *itoa, long size)
{
	if (nb < 0)
	{
		itoa[0] = '-';
		nb *= -1;
	}
	if (nb > 9)
		ft_nbr_to_str(nb / 10, itoa, size - 1);
	itoa[size] = nb % 10 + '0';
}

char	*gc_itoa(int n)
{
	long	nb;
	long	size;
	char	*itoa;

	nb = n;
	size = ft_nb_size(nb);
	itoa = gc_mem(MALLOC, (size + 1), NULL);
	if (!itoa)
		return (NULL);
	if (nb < 0)
		itoa[0] = '-';
	ft_nbr_to_str(nb, itoa, size - 1);
	itoa[size] = '\0';
	return (itoa);
}

void	ciao(int exit_status)
{
	printf(MAGENTA);
	printf("\e[4mCIAO BABY!\e[0m\n");
	printf(RESET);
	gc_mem(FULL_CLEAN, 0, NULL);
	exit(exit_status);
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
