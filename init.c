#include "includes/cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->res_x = 0;
	data->res_y = 0;
	data->no_path = NULL;
	data->so_path = NULL;
	data->we_path = NULL;
	data->ea_path = NULL;
	data->s_path = NULL;
	data->deltaDistX = 0;
	data->deltaDistY = 0;
	data->sideDistX = 0;
	data->sideDistY = 0;
	data->stepX = 0;
	data->stepY = 0;
	data->f_color = 0;
	data->c_color = 0;
	data->map = NULL;
	data->map_x = 0;
	data->map_y = 0;
	data->map_width = 0;
	data->map_height = -1;
	data->charac = 0;
	data->right = 0;
	data->left = 0;
	data->up = 0;
	data->down = 0;
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
