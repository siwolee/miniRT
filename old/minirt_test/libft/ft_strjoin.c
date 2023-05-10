/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:26:54 by juhyulee          #+#    #+#             */
/*   Updated: 2023/04/17 21:18:48 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*news;
	size_t	i;
	size_t	c;

	if (!s1)
		return (ft_strdup(""));
	if (!s1 || !s2)
		return (0);
	news = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (news == 0)
		return (0);
	i = -1;
	c = 0;
	if (s1)
		while (s1[++i] != 0)
			news[i] = s1[i];
	while (s2[c] != 0)
		news[i++] = s2[c++];
	news[ft_strlen(s1) + ft_strlen(s2)] = 0;
	free(s1);
	return (news);
}
