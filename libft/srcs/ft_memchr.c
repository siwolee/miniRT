/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:55:25 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/11 17:49:20 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	uc;
	int				i;

	uc = (unsigned char)c;
	i = 0;
	while (n && *(unsigned char *)(s + i) != uc)
	{
		n--;
		i++;
	}
	if (n == 0)
		return (0);
	else
		return ((void *)s + i);
}
