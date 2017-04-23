/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emasiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:34:11 by emasiuk           #+#    #+#             */
/*   Updated: 2017/03/31 12:34:12 by emasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_all(t_wolf *wolf)
{
	wolf->mlx = mlx_init();
	wolf->win = mlx_new_window(wolf->mlx, 1024, 768, "Wolf3D");
	wolf->image = mlx_new_image(wolf->mlx, 1024, 768);
	wolf->st_x = 3;
	wolf->st_y = 3;
	wolf->st_dir_x = -1;
	wolf->st_dir_y = 0;
	wolf->plane_x = 0;
	wolf->plane_y = 0.66;
	wolf->time = 0;
	wolf->old_time = 0;
	wolf->hit = 0;
	wolf->a = 0;
	wolf->w = 0;
	wolf->d = 0;
	wolf->s = 0;
}

void	walls(t_wolf *wolf)
{
	wolf->wall_w = 1;
	wolf->wall_h = 1;
	wolf->wall_img = mlx_xpm_file_to_image(wolf->mlx, "wood.xpm", &wolf->wall_w,
		&wolf->wall_h);
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
	if (x > 0 && x < 1024 && y > 0 && y < 768)
		memcpy((void *)(image + y * 1024 * (bpp / 8)) + x * (bpp / 8),
		(void *)&tmp, 4);
}

int		main(void)
{
	t_wolf wolf;

	init_all(&wolf);
	read_map(&wolf);
	walls(&wolf);
	calc_ray(&wolf);
	mlx_loop_hook(wolf.mlx, hooks, &wolf);
	mlx_loop(wolf.mlx);
}
