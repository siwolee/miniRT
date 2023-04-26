/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/02 16:21:28 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n_len;
	char	*hay;

	hay = (char *)haystack;
	if (*needle == 0)
		return (hay);
	if (len < ft_strlen(needle))
		return (0);
	while (len && *hay != '\0')
	{
		if (*hay == needle[0])
		{
			n_len = 1;
			while (needle[n_len] != '\0' && needle[n_len] == hay[n_len])
				n_len ++;
			if (needle[n_len] == '\0' && n_len <= len)
				return (hay);
		}
		hay++;
		len--;
	}
	return (0);
}
