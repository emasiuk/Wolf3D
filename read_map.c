/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emasiuk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 12:35:25 by emasiuk           #+#    #+#             */
/*   Updated: 2017/03/31 12:35:26 by emasiuk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		height_map(int fd)
{
	int		count;
	char	*str;

	count = 0;
	while (get_next_line(fd, &str))
	{
		count++;
		ft_strdel(&str);
	}
	ft_strdel(&str);
	return (count);
}

void	read_map(t_wolf *wolf)
{
	int		fd;
	char	*str;
	int		max;
	int		i;

	i = -1;
	fd = open("map", O_RDONLY);
	max = height_map(fd);
	wolf->map = (char **)malloc(sizeof(char *) * (max + 1));
	wolf->map[max] = NULL;
	close(fd);
	fd = open("map", O_RDONLY);
	while (get_next_line(fd, &str))
	{
		wolf->map[++i] = ft_strdup(str);
		ft_strdel(&str);
	}
	ft_strdel(&str);
	close(fd);
	wolf->s_y = i;
	wolf->s_x = ft_strlen(wolf->map[i]);
}
