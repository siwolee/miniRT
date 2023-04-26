/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haecho <haecho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:37:36 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/12 13:00:44 by haecho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;
	size_t	s_len;
	size_t	idx;

	d_len = 0;
	s_len = 0;
	idx = -1;
	while (dst[d_len])
		d_len++;
	while (src[s_len])
		s_len++;
	if (d_len >= dstsize)
		return (s_len + dstsize);
	if (dstsize == 0)
		return (s_len);
	while (src[++idx] && idx + d_len < dstsize - 1)
		dst[d_len + idx] = src[idx];
	dst[d_len + idx] = 0;
	return (d_len + s_len);
}
