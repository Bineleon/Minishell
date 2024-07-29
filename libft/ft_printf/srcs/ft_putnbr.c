/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bineleon <neleon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:19:53 by neleon            #+#    #+#             */
/*   Updated: 2024/07/29 17:46:34 by bineleon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_uitochar(va_list ap, int *count)
{
	long	nb;

	nb = va_arg(ap, unsigned int);
	ft_putnbr(nb, count);
}

void	ft_itochar(va_list ap, int *count)
{
	long	nb;

	nb = va_arg(ap, int);
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
		*count += 1;
	}
	ft_putnbr(nb, count);
}

void	ft_putnbr(long nb, int *count)
{
	if (nb > 9)
		ft_putnbr(nb / 10, count);
	ft_putchar_fd(nb % 10 + '0', 1);
	*count += 1;
}
