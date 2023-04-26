/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 20:59:35 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/11 17:24:24 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	uc;
	void			*result;

	uc = (unsigned char)c;
	result = b;
	while (len)
	{
		*(unsigned char *)b = uc;
		b++;
		len--;
	}
	return (result);
}
