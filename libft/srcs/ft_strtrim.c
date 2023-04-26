/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2023/03/02 16:09:13 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	get_set(char *set, int arr[256])
{
	int	c;

	c = 0;
	while (c < 256)
	{
		arr[c] = 0;
		c++;
	}
	while (*set != '\0')
	{
		arr[(int)*set] = 1;
		set++;
	}
}

static char	*exception(char const *s1, char const *set)
{
	char	*res;

	if (!s1 || !set)
	{
		if (!s1)
			res = ft_calloc(1, 1);
		else
			res = ft_strdup(s1);
		if (!res)
			return (0);
		return (res);
	}
	else
		return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		chk[256];
	char	*res;
	int		start;
	int		end;

	get_set((char *)set, chk);
	if (!s1 || !set)
		return (exception(s1, set));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (chk[(int)s1[start]] == 1)
		start++;
	while (end > start && chk[(int)s1[end]] == 1)
		end--;
	res = ft_calloc(1, end - start + 2);
	if (!res)
		return (0);
	ft_strlcpy(res, s1 + start, end - start + 2);
	return (res);
}
