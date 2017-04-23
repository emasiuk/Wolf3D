/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emasiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:33:40 by emasiuk           #+#    #+#             */
/*   Updated: 2017/03/31 12:33:47 by emasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _WOLF_H
# define _WOLF_H
# define RAD (0.0175433)
# include "mlx.h"
# include <math.h>
# include "libft/libft.h"
# include <fcntl.h>
# include <time.h>

typedef	struct		s_wolf
{
	char			**map;
	void			*mlx;
	void			*win;
	void			*image;
	double			st_dir_x;
	double			st_dir_y;
	double			st_x;
	double			st_y;
	double			plane_x;
	double			plane_y;
	double			time;
	double			old_time;
	double			cam_x;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	int				map_x;
	int				map_y;
	double			dist_side_x;
	double			dist_side_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	double			perp_wall_dist;
	int				line_h;
	int				draw_st;
	int				draw_end;
	int				color;
	double			frame_time;
	int				a;
	int				s;
	int				d;
	int				w;
	double			old_dir_x;
	double			old_plane_x;
	int				s_x;
	int				s_y;
	void			*wall_img;
	int				wall_h;
	int				wall_w;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			move_speed;
	double			r_sp;
}					t_wolf;

void				ft_image_pixel_put(t_wolf *wolf, int x, int y, int rgb);
void				print_line(int x, t_wolf *wolf, int y0, int y1);
void				print_floor(int x, t_wolf *wolf, int y);
void				print_ceiling(int x, t_wolf *wolf);
void				walls(t_wolf *wolf);
void				right(t_wolf *wolf);
void				left(t_wolf *wolf);
void				upered(t_wolf *wolf);
void				back(t_wolf *wolf);
int					hooks(t_wolf *wolf);
void				calc_ray(t_wolf *wolf);
int					height_map(int fd);
void				read_map(t_wolf *wolf);
void				calc_height(t_wolf *wolf);
void				next_square(t_wolf *wolf);
void				calc_step(t_wolf *wolf);
void				calc_ray(t_wolf *wolf);

#endif
