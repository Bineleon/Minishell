/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 20:03:45 by neleon            #+#    #+#             */
/*   Updated: 2024/12/13 14:46:16 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
  	if (!s || fd < 0)
		  return (-1);
		while (*s)
		{
			if (write(fd, s, 1) == -1)
				return (-1);
			s++;
		}
	return (0);
}
// int main(void)
// {
//     ft_putstr_fd("Coucou", 1);
//     return (0);
// }
