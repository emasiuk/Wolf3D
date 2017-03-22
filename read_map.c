#include "wolf.h"

int		height_map(int fd)
{
	int count;
	char *str;

	count = 0;
	while (get_next_line(fd, &str))
		count++;
	return (count);
}

void	read_map(t_wolf *wolf)
{
	int fd;
	char *str;
	int max;
	int i;

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
		printf("%s\n", wolf->map[i]);
	}
}
