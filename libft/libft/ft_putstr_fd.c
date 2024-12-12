/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: neleon <neleon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:03:45 by neleon            #+#    #+#             */
/*   Updated: 2024/12/12 15:46:10 by neleon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (s)
	{
		while (*s)
		{
			if (write(fd, s, 1) == -1)
				return (-1);
			s++;
		}
	}
	return (0);
}
// int main(void)
// {
//     ft_putstr_fd("Coucou", 1);
//     return (0);
// }
