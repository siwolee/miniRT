/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haecho <haecho@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/22 14:16:53 by haecho           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;
	char	*ss;

	i = 0;
	cc = (char)c;
	ss = (char *)s;
	if (*ss == '\0' && cc == '\0')
		return (ss);
	while (ss[i] != '\0')
	{
		if (ss[i] == cc)
			return (ss + i);
		i++;
	}
	if (cc == '\0')
		return (ss + i);
	return (0);
}
