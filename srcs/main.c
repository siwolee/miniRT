/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyulee <juhyulee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 15:44:16 by juhyulee          #+#    #+#             */
/*   Updated: 2023/05/22 17:08:14 by juhyulee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/miniRT.h"

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	t_data	image;
	t_scene	scene;
}	t_vars;

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *vars)
{
	if(keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	return (0);
}

//
t_scene	scene_init(void)
{
	t_scene		scene;
	// t_object	*world;
	// double		ka;

	// if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
	// 	return (NULL);
	// scene->canvas_height = 800;
	// scene->canvas_width = 500;
	scene.canvas = canvas(500, 1000);
	scene.camera = camera(vec(0,0,1), vec(0, 0, -1), vec(0, 1, 0), 90, (double)1/2);
	scene.world = NULL;
	// scene.world = object(SP, sphere(vec(-2, 0, -5), 2), vec(0.5, 0, 0));
	// oadd(&world, object(SP, sphere(vec(0, -1000, 0), 995), vec(1, 1, 1)));
	// oadd(&world, object(SP, sphere(vec(2, 0, -5), 2), vec(0, 0.5, 0)));
	// oadd(&world, object(SP, sphere(vec(0, 7, -5), 3), vec(1, 1, 1)));
	//oadd(&world, object(PL, plane(vec(2, 0, -100), vec(0.5, 0, 0.5)), vec(0.2, 0.2, 0.2)));
	// oadd(&world, object(CY, cylinder(vec(0, 2, -5), vec(0, 0.5, 0.2), 2, 6), vec(0, 0, 0.5)));
	// scene.world = world;
	t_object	*lights;
	lights = object(LIGHT_POINT, light_point(vec(0, 0, 5),
	vec(1, 1, 1), 0.5), vec(0, 0, 0));
	scene.light = lights;
	// scene.light = NULL;
	// ka = 0.1;
	// scene.ambient = vmuln(vec(1, 1, 1), ka);
	return (scene);
}

// //원본 함수에서 바뀐 점 :
// //	동적할당 없앰 ->scene은 메인 함수에서 선언
// t_scene temp_init(void)
// {//화면쳐다보는기준으로 위쪽이y, 오른쪽이 x, 뒤쪽 방향으로 z
// 	t_scene		scene;
// 	t_object	*world;
// 	t_object	*lights;
// 	double		ka;

// 	// if (!(scene = (t_scene *)malloc(sizeof(t_scene))))
// 	// 	return (NULL);
// 	// scene->canvas_height = 800;
// 	// scene->canvas_width = 500;
// 	scene.canvas = canvas(500, 800);
// 	scene.camera = camera(&scene.canvas, vec(0, 0, 6));
// 	world = object(SP, sphere(vec(-2, 0, -5), 2), vec(0.5, 0, 0));
// 	oadd(&world, object(SP, sphere(vec(0, -1000, 0), 995), vec(1, 1, 1)));
// 	oadd(&world, object(SP, sphere(vec(2, 0, -5), 2), vec(0, 0.5, 0)));
// 	oadd(&world, object(SP, sphere(vec(0, 7, -5), 3), vec(1, 1, 1)));
// 	//oadd(&world, object(PL, plane(vec(2, 0, -100), vec(0.5, 0, 0.5)), vec(0.2, 0.2, 0.2)));
// 	oadd(&world, object(CY, cylinder(vec(0, 2, -5), vec(0, 0.5, 0.2), 2, 6), vec(0, 0, 0.5)));
// 	scene.world = world;
// 	lights = object(LIGHT_POINT, light_point(vec(0, 0, 5), vec(1, 1, 1), 0.5), vec(0, 0, 0));
// 	scene.light = lights;
// 	ka = 0.1;
// 	scene.ambient = vmuln(vec(1, 1, 1), ka);
// 	return (scene);
// }

// // 랜더링
// // P3 는 색상값이 아스키코드라는 뜻, 그리고 다음 줄은 캔버스의 가로, 세로 픽셀 수, 마지막은 사용할 색상값
void	ft_draw(t_scene *scene, t_data *image)
{
	int i;
	int j;
	double u;
	double v;
	t_color pixel_color;

	j = scene->canvas.height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < scene->canvas.width)
		{
			u = (double)i / (scene->canvas.width - 1);
			v = (double)j / (scene->canvas.height - 1);
			scene->ray = ray_primary(&scene->camera, u, v);
			pixel_color = ray_color(scene);
			my_mlx_pixel_put(image, i, scene->canvas.height - 1 - j, \
			create_trgb(0, pixel_color.x * 255.999, pixel_color.y * 255.999, pixel_color.z * 255.999));
			++i;
		}
		--j;
	}
}

void	ft_init_mlx(t_vars *vars, t_scene *scene, t_data *image)
{
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, scene->canvas.width, scene->canvas.height, "For team");
	image->img = mlx_new_image(vars->mlx, scene->canvas.width, scene->canvas.height); // 이미지 객체 생성
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,\
	&image->line_length, &image->endian);
}

void	exit_error(int code)
{
	if (code == ERROR_NO_INPUT)
	{
		printf("no file input\n");
	}
	// else if (code == )
	// 	printf("too many arguments\n");
	else if (code == ERROR_CANNOT_OPEN_FILE)
		printf("cannot open file\n");
	else if (code == ERROR_PARSE)
		printf("parsing error\n");
	else
		printf("error not specified yet : %d\n", code);

	exit(1);
}

int file_check(int ac, char **av)
{
	int	fd;

	if (ac != 2)
		exit_error(ERROR_NO_INPUT);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		exit_error(2);
	}
	return (fd);

	// av[ac - 1] = 0;
	// printf("not doing input file right now\n");
	// return (1);
}

// //redraw when camera is changed
// int tilt_camera();
// {
// 	if (keycode == 13)
// 		scene.camera.dir.y += 0.1;
// 	else if (keycode == 1)
// 		scene.camera.dir.y -= 0.1;
// 	else if (keycode == 0)
// 		scene.camera.dir.x -= 0.1;
// 	else if (keycode == 2)
// 		scene.camera.dir.y += 0.1;
// 	ft_draw(&scene, &image);
// }


#define VAL 10
// controling key in keyboard
int	key_press(int keycode, t_vars *vars)
{
	t_camera		*cam;
	t_vec			vup;

	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	vup = vars->scene.camera.orig;
	//orig->카메라 위치(lookfrom)
	//vup->시점각도..?
	if (keycode == 13)
		vup = vec(vup.x, vup.y + VAL, vup.z);
	else if (keycode == 1)
		vup = vec(vup.x, vup.y - VAL, vup.z);
	else if (keycode == 0)
		vup = vec(vup.x + VAL, vup.y, vup.z);
	else if (keycode == 2)
		vup = vec(vup.x - VAL, vup.y, vup.z);
	else
		return (0);
	cam = &vars->scene.camera;
	//여기서도 바꿔줘야함
	vars->scene.camera = camera(vup, cam->dir, cam->vup, cam->fov, cam->aspect);
	ft_draw(&vars->scene, &vars->image);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	return (0);
}

// //norminated version
int	main(int ac, char **av)
// int	main(void)
{
	t_vars	vars;
	int		fd;
	// t_data		image;
	// t_scene		scene;


	fd = file_check(ac, av);
	printf("%d\n", fd);
	vars.scene = scene_init();
	readmap(&vars.scene, fd);
	ft_init_mlx(&vars, &vars.scene, &vars.image);
	ft_draw(&vars.scene, &vars.image);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
	mlx_key_hook(vars.win, key_press, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

