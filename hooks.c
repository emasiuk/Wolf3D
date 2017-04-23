/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emasiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:34:00 by emasiuk           #+#    #+#             */
/*   Updated: 2017/03/31 12:34:03 by emasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		clamp_key(int key, t_wolf *wolf)
{
	(key == 0) ? wolf->a = 1 : 228;
	(key == 1) ? wolf->s = 1 : 228;
	(key == 2) ? wolf->d = 1 : 228;
	(key == 13) ? wolf->w = 1 : 228;
	if (key == 53)
		exit(12);
	return (0);
}

int		release_key(int key, t_wolf *wolf)
{
	(key == 0) ? wolf->a = 0 : 228;
	(key == 1) ? wolf->s = 0 : 228;
	(key == 2) ? wolf->d = 0 : 228;
	(key == 13) ? wolf->w = 0 : 228;
	return (0);
}

int		press_x(void *a)
{
	a = NULL;
	exit(10);
	return (0);
}

int		hooks(t_wolf *wolf)
{
	(wolf->a == 1) ? left(wolf) : 228;
	(wolf->s == 1) ? back(wolf) : 228;
	(wolf->d == 1) ? right(wolf) : 228;
	(wolf->w == 1) ? upered(wolf) : 228;
	mlx_hook(wolf->win, 2, 1, clamp_key, wolf);
	mlx_hook(wolf->win, 3, 2, release_key, wolf);
	mlx_hook(wolf->win, 17, 0L, press_x, wolf);
	mlx_put_image_to_window(wolf->mlx, wolf->win, wolf->image, 0, 0);
	return (0);
}
