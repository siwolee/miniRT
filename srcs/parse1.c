/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 22:15:56 by juhyulee          #+#    #+#             */
/*   Updated: 2023/06/01 17:21:00 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	parse_point(char **split)
{
	t_vec	temp;

	if (!split[0] || !split[1] || !split[2] || split[3])
		exit_error(ERROR_PARSE);
	temp.x = ft_atod(split[0]);
	temp.y = ft_atod(split[1]);
	temp.z = ft_atod(split[2]);
	return (temp);
}

t_vec	parse_vec(char **split)
{
	t_vec	temp;

	if (!split[0] || !split[1] || !split[2] || split[3])
		exit_error(ERROR_PARSE);
	temp.x = ft_atod(split[0]);
	temp.y = ft_atod(split[1]);
	temp.z = ft_atod(split[2]);
	temp = vunit(temp);
	return (temp);
}

t_vec	parse_vec_normalize_color(char **split)
{
	return (vdivn(parse_point(split), 255));
}

char	*valid_parse_vec(char *str)
{
	char	*temp;
	int		cnt;

	temp = str;
	cnt = 0;
	while (*temp)
	{
		if (*temp == ',')
			cnt++;
		temp++;
	}
	if (cnt != 2)
		exit_error(ERROR_PARSE);
	return (str);
}

void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		printf("freed %s\n", split[i]);
		free(split[i]);
		split[i] = NULL;
		i++;
	}
	free(split);
}
