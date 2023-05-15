/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siwolee <siwolee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:07:25 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/15 17:51:27 by siwolee          ###   ########.fr       */
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

//만약 x, y, z가 없거나 그 다음 인자 있을 경우 false
//parse_vec 후에 컬러값 노멀라이즈 해주는 함수
t_vec	parse_vec_normalize_color(char **split)
{
	return(vdivn(parse_vec(split), 255));
}

//split 이후 에러 방지, str에서 , 개수 세서 3개의 인자 받는지 확인
char *valid_parse_vec(char *str)
{
	char 	*temp;
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

//동적할당한 **char들 해제
void	free_split(char **split)
{
	int		i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
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
}

//진행중 _ 왜 xyz에서 db atoi쓰는지? 모르겠는데 일단 parse_vec(ft_atoi사용)으로 처리
//만약 따로 이유 있을 경우 parse_vec에 함수포인터 받아서 바꾸면 될듯
//복수의 ambient 고려하지 않음
//원래 식 : scene.ambient = vmuln(vec(1, 1, 1), ka)
void	input_ambient(t_scene *scene, char *str)
{
	char	**split;
	char	**temp_color;

	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || split[3])
		exit_error(ERROR_PARSE);
	temp_color = ft_split(split[2], ',');
	scene->ambient = vmuln(parse_vec_normalize_color(temp_color), \
					ft_atod(split[1]));
	free_split(split);
	free_split(temp_color);
}

//ok
void	input_plane(t_scene *scene, char *str)
{
	char	**split;
	char	**temp_center;
	char	**temp_dir;
	char	**temp_color;

	printf("str is %s\n", str);
	split = ft_split(str, ' ');
	if (!split[0] || !split[1] || !split[2] || !split[3] || split[4])
		exit_error(ERROR_PARSE);
	temp_center = ft_split(valid_parse_vec(split[1]), ',');
	temp_dir = ft_split(valid_parse_vec(split[2]), ',');
	temp_color = ft_split(valid_parse_vec(split[3]), ',');
	if (!scene->world)
		scene->world = object(PL, plane(parse_vec(temp_center), 
		parse_vec(temp_dir)), parse_vec(temp_color));
	else
		oadd(&scene->world, object(PL, plane(parse_vec(temp_center), \
		parse_vec(temp_dir)), parse_vec(temp_color)));
	free_split(split);
	free_split(temp_center);
	free_split(temp_dir);
	free_split(temp_color);
}

//check id in front of string, and get code
void	id_check(t_scene *scene, char *str)
{
	if (str[0] == 'A')
		input_ambient(scene, str);
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


//read and parse elements in map file
void readmap(t_scene *scene, int fd)
{
	char	*str;
	// char	*temp;

	str = get_next_line(fd);
	convert_space(str);
	while (str != 0)
	{
		// if (check_parse_error(str))
		// 	exit_error(ERROR_PARSE);
		printf("%s\n", str);
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
