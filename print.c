/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emasiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:35:11 by emasiuk           #+#    #+#             */
/*   Updated: 2017/03/31 12:35:12 by emasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_image_pixel_get(int x, int y, void *img, t_wolf *wolf)
{
	int				b;
	int				s;
	int				e;
	char			*image;
	unsigned int	tmp;

	tmp = 0;
	wolf->color = 0;
	image = mlx_get_data_addr(img, &b, &s, &e);
	if (x >= 0 && x < wolf->wall_w && y >= 0 && y < wolf->wall_h)
		memcpy((void *)(&tmp), (void *)((image + y * wolf->wall_w * (b / 8))
			+ x * (b / 8)), 4);
	return (tmp);
}

void	print_line(int x, t_wolf *wolf, int y0, int y1)
{
	int q;

	q = 0;
	y0 -= 1;
	while (++y0 != y1)
	{
		q = y0 * 2 - 768 + wolf->line_h;
		wolf->tex_y = ((q * wolf->wall_w) / wolf->line_h) / 2;
		wolf->color = ft_image_pixel_get(wolf->tex_x, wolf->tex_y,
		wolf->wall_img, wolf);
		ft_image_pixel_put(wolf, x, y0, wolf->color);
	}
}

void	print_floor(int x, t_wolf *wolf, int y)
{
	ft_image_pixel_put(wolf, x, y, 0x8B4513);
	while (++y <= 768)
		ft_image_pixel_put(wolf, x, y, 0x8B4513);
}

void	print_ceiling(int x, t_wolf *wolf)
{
	int y;

	y = -1;
	while (++y < wolf->draw_st)
		ft_image_pixel_put(wolf, x, y, 0x87CEFF);
}
