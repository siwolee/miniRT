/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:58 by siwolee           #+#    #+#             */
/*   Updated: 2022/11/18 18:07:53 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*min(char *res)
{
	res[0] = '-';
	res[1] = '2';
	res[2] = '1';
	res[3] = '4';
	res[4] = '7';
	res[5] = '4';
	res[6] = '8';
	res[7] = '3';
	res[8] = '6';
	res[9] = '4';
	res[10] = '8';
	res[11] = 0;
	return (res);
}

static char	*exception(int n)
{
	char	*res;

	if (n == 0)
	{
		res = (char *)malloc(sizeof(char) * 2);
		if (!res)
			return (0);
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	else if (n == -2147483648)
	{
		res = (char *)malloc(sizeof(char) * (12));
		if (!res)
			return (0);
		return (min(res));
	}
	else
		return (0);
}

static int	get_len(int n, int sign)
{
	int	len;

	len = 0;
	if (sign == -1)
		len = 1;
	while (++len && n >= 10)
		n /= 10;
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;
	int		sign;

	len = 0;
	sign = 1;
	if (n < 0)
		sign = -1;
	res = exception(n);
	if (n == -2147483648 || n == 0)
		return (res);
	n *= sign;
	len = get_len(n, sign);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	res[len] = 0;
	while (--len >= 0)
	{
		res[len] = n % 10 + '0';
		n /= 10;
	}
	if (sign == -1)
		res[0] = '-';
	return (res);
}
