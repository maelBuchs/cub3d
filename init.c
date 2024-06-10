#include "includes/cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_bzero(data, sizeof(t_data));
	data->map_height = -1;

	return (data);
}

t_cub3d	*init_cube3d(void)
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (NULL);
	cub3d->win_width = 0;
	cub3d->win_height = 0;
	cub3d->posX = 100;
	cub3d->posY = 100;
	cub3d->dirX = -1;
	cub3d->dirY = 0;
	cub3d->planeX = 0;
	cub3d->planeY = 0.66;
	cub3d->worldMap = malloc(sizeof(int *) * 24);
	return (cub3d);
}
