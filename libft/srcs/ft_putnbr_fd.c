/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haecho <haecho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/19 11:59:20 by haecho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	word[12];
	int		i;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	word[0] = (n % 10) * sign + '0';
	n = (n / 10) * sign;
	i = 1;
	while (n != 0)
	{
		word[i] = (n % 10) + '0';
		n = (n / 10);
		i++;
	}
	if (sign == -1)
		ft_putchar_fd('-', fd);
	while (--i >= 0)
		ft_putchar_fd(word[i], fd);
}
