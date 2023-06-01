/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:15:27 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/01 19:25:07 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*p;
	char	*org_p;
	size_t	i;

	s1 = (char *)s1;
	i = 0;
	if (!n)
		return (0);
	p = (char *)malloc(sizeof(char) * n + 1);
	if (!p)
	{
		free((void *)s1);
		return (0);
	}
	org_p = p;
	while (*(s1 + i) && i < n)
	{
		*(p + i) = *(s1 + i);
		i++;
	}
	*(p + i) = 0;
	return (org_p);
}

double	db_under_atoi(const char *str)
{
	double	ans;

	ans = 0;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		ans += (*str - '0');
		ans /= 10;
		str++;
	}
	return (ans);
}

double	db_atoi(const char *str)
{
	double	ans;
	double	sign;

	ans = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		ans *= 10;
		ans += (*str - '0');
		str++;
	}
	return ((int)(ans * sign));
}

//leaks ok
double	ft_atod(const char *str)
{
	int		i;
	double	pos;
	double	neg;
	double	sign;
	char	*temp;

	i = 0;
	sign = 1;
	neg = 0;
	while (str[i] != '.' && str[i])
		i++;
	temp = ft_strndup(str, i);
	pos = db_atoi(temp);
	free(temp);
	if (str[i] == '.')
	{
		temp = ft_strndup(&str[i + 1], ft_strlen(str));
		neg = db_under_atoi(temp);
		free(temp);
	}
	if (pos < 0)
	{
		sign *= -1;
		pos *= -1;
	}
	return ((pos + neg) * sign);
}

void	convert_space(char *c)
{
	if (c == NULL)
		return ;
	while (*c)
	{
		if ((*c == 32 || (*c >= 9 && *c <= 13)))
		{
			*c = 32;
		}
		c++;
	}
}
