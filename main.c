#include "wolf.h"

void	init_all(t_wolf *wolf)
{
	wolf->mlx = mlx_init();
	wolf->win = mlx_new_window(wolf->mlx, 1280, 1024, "Wolf3D");
	wolf->image = mlx_new_image(wolf->mlx, 1280, 1024);
	wolf->st_x = 22;
	wolf->st_y = 12;
	wolf->st_dir_x = -1;
	wolf->st_dir_y = 0;
	wolf->plane_x = 0;
	wolf->plane_y = 0.66;
	wolf->time = 0;
	wolf->old_time = 0;
	wolf->hit = 0;
}

int		my_key_funct(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

void	ft_image_pixel_put(t_wolf *wolf, int x, int y, int rgb)
{
	int				bpp;
	int				sl;
	int				en;
	char			*image;
	unsigned int	tmp;

	image = mlx_get_data_addr(wolf->image, &bpp, &sl, &en);
	tmp = (mlx_get_color_value(wolf->mlx, rgb));
	if (x > 0 && x < 1280 && y > 0 && y < 1024)
		memcpy((void *)(image + y * 1280 * (bpp / 8)) + x * (bpp / 8),
		(void *)&tmp, 4);
}

void	print_line(int x, t_wolf *wolf)
{
	//printf("%d = %d\n", wolf->draw_st, wolf->draw_end);
	ft_image_pixel_put(wolf, x, wolf->draw_st, wolf->color);
	while (++wolf->draw_st < wolf->draw_end)
		ft_image_pixel_put(wolf, x, wolf->draw_st, wolf->color);
}

void	color(t_wolf *wolf)
{
	if (wolf->map[wolf->map_y][wolf->map_x] == '1')
		wolf->color = 0xFF0000;
	if (wolf->map[wolf->map_y][wolf->map_x] == '2')
		wolf->color = 0x00FF00;
	if (wolf->map[wolf->map_y][wolf->map_x] == '3')
		wolf->color = 0x0000FF;
	(wolf->side == 1) ? wolf->color /= 2 : 228;
}

void	calc_height(t_wolf *wolf)
{
	wolf->line_h = (1024 / wolf->perp_wall_dist);
	// printf("perp_wall_dist = %f\n", wolf->perp_wall_dist);
	// printf("line_h = %d\n", wolf->line_h);
	wolf->draw_st = -wolf->line_h / 2 + 1024 / 2;
	(wolf->draw_st < 0) ? wolf->draw_st = 0 : 228;
	wolf->draw_end = wolf->line_h / 2 + 1024 / 2;
	(wolf->draw_end >= 1024) ? wolf->draw_end = 1024 - 1 : 228;
}

void	next_square(t_wolf *wolf)
{
	while (wolf->hit == 0)
	{
		if (wolf->dist_side_x < wolf->dist_side_y)
		{
			wolf->dist_side_x += wolf->delta_dist_x;
			wolf->map_x += wolf->step_x;
			wolf->side = 0;
		}
		else
		{
			wolf->dist_side_y += wolf->delta_dist_y;
			wolf->map_y += wolf->step_y;
			wolf->side = 1;
		}
		if(wolf->map[wolf->map_y][wolf->map_x])
			wolf->hit = 1;
	}
}

void	calc_step(t_wolf *wolf)
{
	if (wolf->dir_x < 0)
	{
		wolf->step_x = -1;
		wolf->dist_side_x = (wolf->pos_x - wolf->map_x) * wolf->delta_dist_x;
	}
	else
	{
		wolf->step_x = 1;
		wolf->dist_side_x = (wolf->map_x + 1.0 - wolf->pos_x) * wolf->delta_dist_x;
	}
	if (wolf->dir_y < 0)
	{
		wolf->step_y = -1;
		wolf->dist_side_y = (wolf->pos_y - wolf->map_y) * wolf->delta_dist_y;
	}
	else
	{
		wolf->step_y = 1;
		wolf->dist_side_y = (wolf->map_y + 1.0 - wolf->pos_y) * wolf->delta_dist_y;
	}
	next_square(wolf);
}

void	calc_ray(t_wolf *wolf)
{
	int x;

	x = -1;
	while (++x < 10)
	{
		wolf->cam_x = 2 * x / 1280. - 1;
		wolf->pos_x = wolf->st_x;
		wolf->pos_y = wolf->st_y;
		wolf->dir_x = wolf->st_dir_x + wolf->plane_x * wolf->cam_x;
		wolf->dir_y = wolf->st_dir_y + wolf->plane_y * wolf->cam_x;
		wolf->map_x = (int)wolf->pos_x;
		wolf->map_y = (int)wolf->pos_y;
		wolf->delta_dist_x = sqrt(1 + (wolf->dir_y * wolf->dir_y) / (wolf->dir_x * wolf->dir_x));
		wolf->delta_dist_y = sqrt(1 + (wolf->dir_x * wolf->dir_x) / (wolf->dir_y * wolf->dir_y));
		calc_step(wolf);
		// printf("side = %d\n", wolf->side);
		printf("x = %d\n", x);
		(wolf->side == 0) ? (wolf->perp_wall_dist = (wolf->map_x - wolf->pos_x + (1 - wolf->step_x) / 2) / wolf->dir_x) : 228;
		(wolf->side != 0) ? (wolf->perp_wall_dist = (wolf->map_y - wolf->pos_y + (1 - wolf->step_y) / 2) / wolf->dir_y) : 228;
		printf("map_y = %d\n pos_y = %f\n step_y = %d\n dir_y = %f\n", wolf->map_y, wolf->pos_y, wolf->step_y, wolf->dir_y);
		calc_height(wolf);
		color(wolf);
		print_line(x, wolf);
	}
}

int		main(void)
{
	t_wolf wolf;

	init_all(&wolf);
	read_map(&wolf);
	calc_ray(&wolf);
	mlx_put_image_to_window(wolf.mlx, wolf.win, wolf.image, 0, 0);
	mlx_key_hook(wolf.win, my_key_funct, &wolf);
	mlx_loop(wolf.mlx);
}
