/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emasiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:34:51 by emasiuk           #+#    #+#             */
/*   Updated: 2017/03/31 12:34:53 by emasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	back(t_wolf *wolf)
{
	wolf->move_speed = 0.05;
	mlx_destroy_image(wolf->mlx, wolf->image);
	wolf->image = mlx_new_image(wolf->mlx, 1024, 768);
	if (wolf->map[(int)(wolf->st_y - wolf->st_dir_y *
		wolf->move_speed)][(int)wolf->st_x] == '0')
		wolf->st_y -= wolf->st_dir_y * wolf->move_speed;
	if (wolf->st_y >= wolf->s_y - 0.1 || wolf->st_y <= 1.1)
		wolf->st_y += wolf->st_dir_y * wolf->move_speed;
	if (wolf->map[(int)wolf->st_y][(int)(wolf->st_x - wolf->st_dir_x *
		wolf->move_speed)] == '0')
		wolf->st_x -= wolf->st_dir_x * wolf->move_speed;
	if (wolf->st_x >= wolf->s_x - 1.1 || wolf->st_x <= 1.1)
		wolf->st_x += wolf->st_dir_x * wolf->move_speed;
	calc_ray(wolf);
}

void	upered(t_wolf *wolf)
{
	wolf->move_speed = 0.05;
	mlx_destroy_image(wolf->mlx, wolf->image);
	wolf->image = mlx_new_image(wolf->mlx, 1024, 768);
	if (wolf->map[(int)wolf->st_y][(int)(wolf->st_x + wolf->st_dir_x *
		wolf->move_speed)] == '0')
		wolf->st_x += wolf->st_dir_x * wolf->move_speed;
	if (wolf->st_x >= wolf->s_x - 1.1 || wolf->st_x <= 1.1)
		wolf->st_x -= wolf->st_dir_x * wolf->move_speed;
	if (wolf->map[(int)(wolf->st_y + wolf->st_dir_y *
		wolf->move_speed)][(int)wolf->st_x] == '0')
		wolf->st_y += wolf->st_dir_y * wolf->move_speed;
	if (wolf->st_y >= wolf->s_y - 0.1 || wolf->st_y <= 1.1)
		wolf->st_y -= wolf->st_dir_y * wolf->move_speed;
	calc_ray(wolf);
}

void	left(t_wolf *wolf)
{
	wolf->r_sp = 0.03;
	mlx_destroy_image(wolf->mlx, wolf->image);
	wolf->image = mlx_new_image(wolf->mlx, 1024, 768);
	wolf->old_dir_x = wolf->st_dir_x;
	wolf->st_dir_x = wolf->st_dir_x * cos(wolf->r_sp) - wolf->st_dir_y *
	sin(wolf->r_sp);
	wolf->st_dir_y = wolf->old_dir_x * sin(wolf->r_sp) + wolf->st_dir_y *
	cos(wolf->r_sp);
	wolf->old_plane_x = wolf->plane_x;
	wolf->plane_x = wolf->plane_x * cos(wolf->r_sp) - wolf->plane_y *
	sin(wolf->r_sp);
	wolf->plane_y = wolf->old_plane_x * sin(wolf->r_sp) + wolf->plane_y *
	cos(wolf->r_sp);
	calc_ray(wolf);
}

void	right(t_wolf *wolf)
{
	wolf->r_sp = 0.03;
	mlx_destroy_image(wolf->mlx, wolf->image);
	wolf->image = mlx_new_image(wolf->mlx, 1024, 768);
	wolf->old_dir_x = wolf->st_dir_x;
	wolf->st_dir_x = wolf->st_dir_x * cos(-wolf->r_sp) - wolf->st_dir_y *
	sin(-wolf->r_sp);
	wolf->st_dir_y = wolf->old_dir_x * sin(-wolf->r_sp) + wolf->st_dir_y *
	cos(-wolf->r_sp);
	wolf->old_plane_x = wolf->plane_x;
	wolf->plane_x = wolf->plane_x * cos(-wolf->r_sp) - wolf->plane_y *
	sin(-wolf->r_sp);
	wolf->plane_y = wolf->old_plane_x * sin(-wolf->r_sp) + wolf->plane_y *
	cos(-wolf->r_sp);
	calc_ray(wolf);
}
