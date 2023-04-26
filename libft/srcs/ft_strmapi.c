/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2022/12/23 23:10:06 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*res;
	size_t	len;

	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = 0;
	i = 0;
	while (s[i])
	{
		res[i] = (*f)((unsigned int)i, s[i]);
		i++;
	}
	return (res);
}
