/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haecho <haecho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/19 11:00:46 by haecho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;

	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, len + 1);
	ft_strlcat(ptr, s2, len + 1);
	return (ptr);
}
