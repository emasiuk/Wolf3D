/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emasiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:35:20 by emasiuk           #+#    #+#             */
/*   Updated: 2017/03/31 12:35:21 by emasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	calc_height(t_wolf *wolf)
{
	wolf->line_h = (int)(768 / wolf->perp_wall_dist);
	wolf->draw_st = -wolf->line_h / 2 + 768 / 2;
	(wolf->draw_st < 0) ? wolf->draw_st = 0 : 228;
	wolf->draw_end = wolf->line_h / 2 + 768 / 2;
	(wolf->draw_end >= 768) ? wolf->draw_end = 768 - 1 : 228;
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
		if (wolf->map[wolf->map_y][wolf->map_x] > '0')
			wolf->hit = 1;
	}
	wolf->hit = 0;
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
		wolf->dist_side_x = (wolf->map_x + 1.0 - wolf->pos_x) *
		wolf->delta_dist_x;
	}
	if (wolf->dir_y < 0)
	{
		wolf->step_y = -1;
		wolf->dist_side_y = (wolf->pos_y - wolf->map_y) * wolf->delta_dist_y;
	}
	else
	{
		wolf->step_y = 1;
		wolf->dist_side_y = (wolf->map_y + 1.0 - wolf->pos_y) *
		wolf->delta_dist_y;
	}
	next_square(wolf);
}

void	norm_func(t_wolf *wolf, int x)
{
	if (wolf->side == 0)
		wolf->wall_x = wolf->pos_y + wolf->perp_wall_dist * wolf->dir_y;
	else
		wolf->wall_x = wolf->pos_x + wolf->perp_wall_dist * wolf->dir_x;
	wolf->wall_x -= floor(wolf->wall_x);
	wolf->tex_x = (int)(wolf->wall_x * (double)wolf->wall_h);
	if (wolf->side == 0 && wolf->dir_x > 0)
		wolf->tex_x = wolf->wall_h - wolf->tex_x - 1;
	if (wolf->side == 1 && wolf->dir_y < 0)
		wolf->tex_x = wolf->wall_h - wolf->tex_x - 1;
	calc_height(wolf);
	print_line(x, wolf, wolf->draw_st, wolf->draw_end);
	print_floor(x, wolf, wolf->draw_end);
	print_ceiling(x, wolf);
}

void	calc_ray(t_wolf *wolf)
{
	int x;

	x = -1;
	while (++x < 1024)
	{
		wolf->cam_x = 2 * x / (double)1024 - 1;
		wolf->pos_x = wolf->st_x;
		wolf->pos_y = wolf->st_y;
		wolf->dir_x = wolf->st_dir_x + wolf->plane_x * wolf->cam_x;
		wolf->dir_y = wolf->st_dir_y + wolf->plane_y * wolf->cam_x;
		wolf->map_x = (int)wolf->pos_x;
		wolf->map_y = (int)wolf->pos_y;
		wolf->delta_dist_x = sqrt(1 + (wolf->dir_y * wolf->dir_y) /
		(wolf->dir_x * wolf->dir_x));
		wolf->delta_dist_y = sqrt(1 + (wolf->dir_x * wolf->dir_x) /
		(wolf->dir_y * wolf->dir_y));
		calc_step(wolf);
		if (wolf->side == 0)
			wolf->perp_wall_dist = (wolf->map_x - wolf->pos_x +
			(1 - wolf->step_x) / 2) / wolf->dir_x;
		else
			wolf->perp_wall_dist = (wolf->map_y - wolf->pos_y +
			(1 - wolf->step_y) / 2) / wolf->dir_y;
		norm_func(wolf, x);
	}
}
