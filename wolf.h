#ifndef _WOLF_H
# define _WOLF_H
# define RAD (0.0175433)
# include "mlx.h"
# include <math.h>
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef	struct		s_wolf
{
	char **map;
	void *mlx;
	void *win;
	void *image;
	double st_dir_x; //initial direction vector
	double st_dir_y; //initial direction vector
	double st_x; //start position on map
	double st_y; //start position on map
	double plane_x;
	double plane_y;
	double time; // current frame
	double old_time; //previous frame
	double cam_x; // coord x in camera space
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	int map_x;
	int map_y;
	double dist_side_x; //length of ray from current position to next x-side
	double dist_side_y; //length of ray from current position to next y-side
	double delta_dist_x;
	double delta_dist_y;
	int step_x;
	int step_y;
	int hit;
	int side;
	double perp_wall_dist;
	int line_h;
	int draw_st;
	int draw_end;
	int color;

}					t_wolf;


int		height_map(int fd);
void	read_map(t_wolf *wolf);

#endif
