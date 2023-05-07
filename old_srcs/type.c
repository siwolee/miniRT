/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:07:25 by juhyulee          #+#    #+#             */
/*   Updated: 2023/04/26 19:42:34 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "type.h"

//파싱하고 식별자 구분해서 연결 리스트 구조체에 만들어서 넣어주셈

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

double	ft_atod(const char *str)
{
	int		i;
	double	pos;
	double	neg;
	double	sign;

	i = 0;
	sign = 1;
	neg = 0;
	while (str[i] != '.' && str[i])
		i++;
	pos = db_atoi(ft_strndup(str, i));
	if (str[i] == '.')
		neg = db_under_atoi(ft_strndup(&str[i + 1], ft_strlen(str)));
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

void	input_cylinder(t_main *main, char *str)
{
	t_cylinder	*temp;
	char		**split;
	char		**split2;
	char		**split3;
	char		**split4;

	split = ft_split(str, ' ');
	split2 = ft_split(split[1], ',');
	split3 = ft_split(split[2], ',');
	split4 = ft_split(split[5], ',');
	if (!(main->cylinder))
	{
		main->cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
		main->cylinder->point.x = ft_atod(split2[0]);
		main->cylinder->point.y = ft_atod(split2[1]);
		main->cylinder->point.z = ft_atod(split2[2]);
		main->cylinder->vec.x = ft_atod(split3[0]);
		main->cylinder->vec.y = ft_atod(split3[1]);
		main->cylinder->vec.z = ft_atod(split3[2]);
		main->cylinder->dia = ft_atod(split[3]);
		main->cylinder->height = ft_atod(split[4]);
		main->cylinder->color.x = ft_atod(split4[0]);
		main->cylinder->color.y = ft_atod(split4[1]);
		main->cylinder->color.z = ft_atod(split4[2]);
	}
	else
	{
		while (main->cylinder->next)
			main->cylinder = main->cylinder->next;
		temp = (t_cylinder *)malloc(sizeof(t_cylinder));
		temp->point.x = ft_atod(split2[0]);
		temp->point.y = ft_atod(split2[1]);
		temp->point.z = ft_atod(split2[2]);
		temp->vec.x = ft_atod(split3[0]);
		temp->vec.y = ft_atod(split3[1]);
		temp->vec.z = ft_atod(split3[2]);
		temp->dia = ft_atod(split[3]);
		temp->height = ft_atod(split[4]);
		temp->color.x = ft_atod(split4[0]);
		temp->color.y = ft_atod(split4[1]);
		temp->color.z = ft_atod(split4[2]);
		main->cylinder->next = temp;
	}
}

void	input_sphere(t_main *main, char *str)
{
	t_sphere	*temp;
	char		**split;
	char		**split2;
	char		**split3;

	split = ft_split(str, ' ');
	split2 = ft_split(split[1], ',');
	split3 = ft_split(split[3], ',');
	if (!(main->sphere))
	{
		main->sphere = (t_sphere *)malloc(sizeof(t_sphere));
		main->sphere->point.x = ft_atod(split2[0]);
		main->sphere->point.y = ft_atod(split2[1]);
		main->sphere->point.z = ft_atod(split2[2]);
		main->sphere->dia = ft_atod(split[2]);
		main->sphere->color.x = ft_atod(split3[0]);
		main->sphere->color.y = ft_atod(split3[1]);
		main->sphere->color.z = ft_atod(split3[2]);
	}
	else
	{
		while (main->sphere->next)
			main->sphere = main->sphere->next;
		temp = (t_sphere *)malloc(sizeof(t_sphere));
		temp->point.x = ft_atod(split2[0]);
		temp->point.y = ft_atod(split2[1]);
		temp->point.z = ft_atod(split2[2]);
		temp->dia = ft_atod(split[2]);
		temp->color.x = ft_atod(split3[0]);
		temp->color.y = ft_atod(split3[1]);
		temp->color.z = ft_atod(split3[2]);
		main->sphere->next = temp;
	}
}

void	input_plane(t_main *main, char *str)
{
	t_plane	*temp;
	char	**split;
	char	**split2;
	char	**split3;
	char	**split4;

	split = ft_split(str, ' ');
	split2 = ft_split(split[1], ',');
	split3 = ft_split(split[2], ',');
	split4 = ft_split(split[3], ',');
	if (!(main->plane))
	{
		main->plane = (t_plane *)malloc(sizeof(t_plane));
		main->plane->point.x = ft_atod(split2[0]);
		main->plane->point.y = ft_atod(split2[1]);
		main->plane->point.z = ft_atod(split2[2]);
		main->plane->vec.x = ft_atod(split3[0]);
		main->plane->vec.y = ft_atod(split3[1]);
		main->plane->vec.z = ft_atod(split3[2]);
		main->plane->color.x = ft_atod(split4[0]);
		main->plane->color.y = ft_atod(split4[1]);
		main->plane->color.z = ft_atod(split4[2]);
	}
	else
	{
		while (main->plane->next)
			main->plane = main->plane->next;
		temp = (t_plane *)malloc(sizeof(t_plane));
		main->plane->point.x = ft_atod(split2[0]);
		main->plane->point.y = ft_atod(split2[1]);
		main->plane->point.z = ft_atod(split2[2]);
		main->plane->vec.x = ft_atod(split3[0]);
		main->plane->vec.y = ft_atod(split3[1]);
		main->plane->vec.z = ft_atod(split3[2]);
		main->plane->color.x = ft_atod(split4[0]);
		main->plane->color.y = ft_atod(split4[1]);
		main->plane->color.z = ft_atod(split4[2]);
		main->plane->next = temp;
	}
}

void	input_light(t_main *main, char *str)
{
	t_light		*temp;
	char		**split;
	char		**split2;
	char		**split3;

	split = ft_split(str, ' ');
	split2 = ft_split(split[1], ',');
	split3 = ft_split(split[3], ',');
	if (!(main->light))
	{
		main->light = (t_light *)malloc(sizeof(t_light));
		main->light->point.x = ft_atod(split2[0]);
		main->light->point.y = db_atoi(split2[1]);
		main->light->point.z = db_atoi(split2[2]);
		main->light->bright = ft_atod(split[2]);
		main->light->color.x = db_atoi(split3[0]);
		main->light->color.y = db_atoi(split3[1]);
		main->light->color.z = db_atoi(split3[2]);
	}
	else
	{
		while (main->light->next)
			main->light = main->light->next;
		temp = (t_light *)malloc(sizeof(t_light));
		temp->point.x = ft_atod(split2[0]);
		temp->point.y = db_atoi(split2[1]);
		temp->point.z = db_atoi(split2[2]);
		temp->bright = ft_atod(split[2]);
		temp->color.x = db_atoi(split3[0]);
		temp->color.y = db_atoi(split3[1]);
		temp->color.z = db_atoi(split3[2]);
		main->light->next = temp;
	}
}

void	input_camera(t_main *main, char *str)
{
	t_camera	*temp;
	char		**split;
	char		**split2;
	char		**split3;

	split = ft_split(str, ' ');
	split2 = ft_split(split[1], ',');
	split3 = ft_split(split[2], ',');
	if (!(main->cam))
	{
		main->cam = (t_camera *)malloc(sizeof(t_camera));
		main->cam->point.x = db_atoi(split2[0]);
		main->cam->point.y = db_atoi(split2[1]);
		main->cam->point.z = db_atoi(split2[2]);
		main->cam->vec.x = db_atoi(split3[0]);
		main->cam->vec.y = db_atoi(split3[1]);
		main->cam->vec.z = db_atoi(split3[2]);
		main->cam->fov = ft_atod(split[3]);
		main->cam->next = NULL;
	}
	else
	{
		while (main->cam->next)
			main->cam = main->cam->next;
		temp = (t_camera *)malloc(sizeof(t_camera));
		temp->point.x = db_atoi(split2[0]);
		temp->point.y = db_atoi(split2[1]);
		temp->point.z = db_atoi(split2[2]);
		temp->vec.x = db_atoi(split3[0]);
		temp->vec.y = db_atoi(split3[1]);
		temp->vec.z = db_atoi(split3[2]);
		main->cam->fov = db_atoi(split[3]);
		main->cam->next = temp;
	}
}

void	input_ambient(t_main *main, char *str)
{
	char	**split;
	char	**split2;

	split = ft_split(str, ' ');
	split2 = ft_split(split[2], ',');
	main->ambient.range = ft_atod(split[1]);
	main->ambient.color.x = db_atoi(split2[0]);
	main->ambient.color.y = db_atoi(split2[1]);
	main->ambient.color.z = db_atoi(split2[2]);
}

void	id_check(t_main *main, char *str)
{
	if (str[0] == 'A')
		input_ambient(main, str);
	else if (str[0] == 'C')
		input_camera(main, str);
	else if (str[0] == 'L')
		input_light(main, str);
	else if (ft_strncmp(str, "pl", 2) == 0)
		input_plane(main, str);
	else if (ft_strncmp(str, "sp", 2) == 0)
		input_sphere(main, str);
	else if (ft_strncmp(str, "cy", 2) == 0)
		input_cylinder(main, str);
	else
		printf("nothing\n");
}

void readmap(t_main *main, char **av)
{
	int		fd;
	char	*str;
	char	*temp;

	fd = open(av[1], O_RDONLY);
	str = get_next_line(fd);
	convert_space(str);
	temp = str;
	while (str != 0)
	{
		id_check(main, str);
		free(str);
		str = NULL;
		str = get_next_line(fd);
		convert_space(str);
		if (str && ft_strlen(str) == 1)
			printf("error\n");
	}
	free(str);
	temp = 0;
}

void	printmap(t_main *main)
{
	printf("%f\n",main->plane->color.x);
	// printf("%f\n",main->);
	// printf("%f\n",main->);
	// printf("%f\n",main->);
	// printf("%f\n",main->);
	// printf("%f\n",main->
}

// int main(int ac, char **av)
// {
// 	t_main main;

// 	if (ac != 2)
// 		return (0);
// 	//.rt 확장자 체크하는 함수
// 	readmap(&main, av);

// 	return (0);
// }