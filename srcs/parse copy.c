/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:07:25 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/15 12:21:04 by siwolee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

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

//converting white space to normal space
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

void	input_cylinder(t_scene *scene, char *str)
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
	if (!(scene->cylinder))
	{
		scene->cylinder = (t_cylinder *)malloc(sizeof(t_cylinder));
		scene->cylinder->point.x = ft_atod(split2[0]);
		scene->cylinder->point.y = ft_atod(split2[1]);
		scene->cylinder->point.z = ft_atod(split2[2]);
		scene->cylinder->vec.x = ft_atod(split3[0]);
		scene->cylinder->vec.y = ft_atod(split3[1]);
		scene->cylinder->vec.z = ft_atod(split3[2]);
		scene->cylinder->dia = ft_atod(split[3]);
		scene->cylinder->height = ft_atod(split[4]);
		scene->cylinder->color.x = ft_atod(split4[0]);
		scene->cylinder->color.y = ft_atod(split4[1]);
		scene->cylinder->color.z = ft_atod(split4[2]);
	}
	else
	{
		while (scene->cylinder->next)
			scene->cylinder = scene->cylinder->next;
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
		scene->cylinder->next = temp;
	}
}

void	input_sphere(t_scene *scene, char *str)
{
	t_sphere	*temp;
	char		**split;
	char		**split2;
	char		**split3;

	split = ft_split(str, ' ');
	split2 = ft_split(split[1], ',');
	split3 = ft_split(split[3], ',');
	if (!(scene->sphere))
	{
		scene->sphere = (t_sphere *)malloc(sizeof(t_sphere));
		scene->sphere->point.x = ft_atod(split2[0]);
		scene->sphere->point.y = ft_atod(split2[1]);
		scene->sphere->point.z = ft_atod(split2[2]);
		scene->sphere->dia = ft_atod(split[2]);
		scene->sphere->color.x = ft_atod(split3[0]);
		scene->sphere->color.y = ft_atod(split3[1]);
		scene->sphere->color.z = ft_atod(split3[2]);
	}
	else
	{
		while (scene->sphere->next)
			scene->sphere = scene->sphere->next;
		temp = (t_sphere *)malloc(sizeof(t_sphere));
		temp->point.x = ft_atod(split2[0]);
		temp->point.y = ft_atod(split2[1]);
		temp->point.z = ft_atod(split2[2]);
		temp->dia = ft_atod(split[2]);
		temp->color.x = ft_atod(split3[0]);
		temp->color.y = ft_atod(split3[1]);
		temp->color.z = ft_atod(split3[2]);
		scene->sphere->next = temp;
	}
}

//만약 x, y, z가 없거나 그 다음 인자 있을 경우 false
t_vec	parse_vec(char **split)
{
	t_vec	temp;

	if (!split[0] || !split[1] || !split[2] || split[3])
		exit_error(ERROR_PARSE);
	temp.x = ft_atod(split[0]);
	temp.y = ft_atod(split[1]);
	temp.z = ft_atod(split[2]);
	return (temp);
}

//수정중
void	input_plane(t_scene *scene, char *str)
{
	char	**split;
	char	**temp_center;
	char	**temp_dir;
	char	**temp_color;

	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || split[3])
		exit_error(ERROR_PARSE);
	temp_center = ft_split(split[1], ',');
	temp_dir = ft_split(split[2], ',');
	temp_color = ft_split(split[3], ',');
	if (!scene->world)
		scene->world = object(PL, plane(parse_vec(temp_center), 
		parse_vec(temp_dir)), parse_vec(temp_color));
	else
		oadd(&scene->world, object(PL, plane(parse_vec(temp_center), \
		parse_vec(temp_dir)), parse_vec(temp_color)));
	//free_split(split);
}

void	input_light(t_scene *scene, char *str)
{
	t_light		*temp;
	char		**split;
	char		**split2;
	char		**temp_dir;

	split = ft_split(str, ' ');
	split2 = ft_split(split[1], ',');
	split3 = ft_split(split[3], ',');
	if (!(scene->light))
	{
		scene->light = (t_light *)malloc(sizeof(t_light));
		scene->light->point.x = ft_atod(split2[0]);
		scene->light->point.y = db_atoi(split2[1]);
		scene->light->point.z = db_atoi(split2[2]);
		scene->light->bright = ft_atod(split[2]);
		scene->light->color.x = db_atoi(split3[0]);
		scene->light->color.y = db_atoi(split3[1]);
		scene->light->color.z = db_atoi(split3[2]);
	}
	else
	{
		while (scene->light->next)
			scene->light = scene->light->next;
		temp = (t_light *)malloc(sizeof(t_light));
		temp->point.x = ft_atod(split2[0]);
		temp->point.y = db_atoi(split2[1]);
		temp->point.z = db_atoi(split2[2]);
		temp->bright = ft_atod(split[2]);
		temp->color.x = db_atoi(split3[0]);
		temp->color.y = db_atoi(split3[1]);
		temp->color.z = db_atoi(split3[2]);
		scene->light->next = temp;
	}
}

void	input_camera(t_scene *scene, char *str)
{
	t_camera	*temp;
	char		**split;
	char		**split2;
	char		**split3;

	split = ft_split(str, ' ');
	split2 = ft_split(split[1], ',');
	split3 = ft_split(split[2], ',');
	if (!(scene->cam))
	{
		scene->cam = (t_camera *)malloc(sizeof(t_camera));
		scene->cam->point.x = db_atoi(split2[0]);
		scene->cam->point.y = db_atoi(split2[1]);
		scene->cam->point.z = db_atoi(split2[2]);
		scene->cam->vec.x = db_atoi(split3[0]);
		scene->cam->vec.y = db_atoi(split3[1]);
		scene->cam->vec.z = db_atoi(split3[2]);
		scene->cam->fov = ft_atod(split[3]);
		scene->cam->next = NULL;
	}
	else
	{
		while (scene->cam->next)
			scene->cam = scene->cam->next;
		temp = (t_camera *)malloc(sizeof(t_camera));
		temp->point.x = db_atoi(split2[0]);
		temp->point.y = db_atoi(split2[1]);
		temp->point.z = db_atoi(split2[2]);
		temp->vec.x = db_atoi(split3[0]);
		temp->vec.y = db_atoi(split3[1]);
		temp->vec.z = db_atoi(split3[2]);
		scene->cam->fov = db_atoi(split[3]);
		scene->cam->next = temp;
	}
}

void	input_ambient(t_scene *scene, char *str)
{
	char	**split;
	char	**split2;

	split = ft_split(str, ' ');
	split2 = ft_split(split[2], ',');
	scene->ambient.range = ft_atod(split[1]);
	scene->ambient.color.x = db_atoi(split2[0]);
	scene->ambient.color.y = db_atoi(split2[1]);
	scene->ambient.color.z = db_atoi(split2[2]);
}

//check id in front of string, and get code
void	id_check(t_scene *scene, char *str)
{
	// if (str[0] == 'A')
	// 	input_ambient(scene, str);
	// if (str[0] == 'C')
	// 	input_camera(scene, str);
	// else if (str[0] == 'L')
	// 	input_light(scene, str);
	if (ft_strncmp(str, "pl", 2) == 0)
		input_plane(scene, str);
	// else if (ft_strncmp(str, "sp", 2) == 0)
	// 	input_sphere(scene, str);
	// else if (ft_strncmp(str, "cy", 2) == 0)
	// 	input_cylinder(scene, str);
	else
		printf("nothing\n");
}

//checking if is available for parsing
int check_parse_error(str);


//check if world is unvalid : 
// - no light
//not finished
int check_world_error(t_scene *scene)
{
	if (scene->light == NULL)
		return (1);
	else
		return (0);
}

//read and parse elements in map file
void readmap(t_scene *scene, int fd)
{
	char	*str;
	char	*temp;

	str = get_next_line(fd);
	convert_space(str);
	while (str != 0)
	{
		// if (check_parse_error(str))
		// 	exit_error(ERROR_PARSE);
		id_check(scene, str);
		free(str);
		str = NULL;
		str = get_next_line(fd);
		convert_space(str);
	}
	free(str);
	// if (check_world_error(scene))
	// 	exit_error(ERROR_NO_ELEMENT);
}

void	printmap(t_scene *scene)
{
	printf("%f\n",scene->plane->color.x);
	// printf("%f\n",scene->);
	// printf("%f\n",scene->);
	// printf("%f\n",scene->);
	// printf("%f\n",scene->);
	// printf("%f\n",scene->
}