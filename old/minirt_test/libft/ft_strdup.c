/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:44:08 by juhyulee          #+#    #+#             */
/*   Updated: 2023/04/17 21:06:55 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*t;

	if (s == 0)
		return (0);
	i = ft_strlen(s);
	t = malloc((i + 1));
	if (t == 0)
		return (0);
	ft_memcpy(t, s, i);
	t[i] = 0;
	return (t);
}
