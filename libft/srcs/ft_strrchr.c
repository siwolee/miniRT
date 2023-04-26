/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haecho <haecho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/22 14:36:18 by haecho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	char	cc;
	int		len;

	ptr = (char *)s;
	cc = (char)c;
	if (*ptr == '\0' && cc == '\0')
		return (ptr);
	len = ft_strlen(ptr);
	if (cc == '\0')
		return (ptr + len);
	while (--len >= 0)
	{
		if (ptr[len] == cc)
			return (ptr + len);
	}
	return (0);
}
