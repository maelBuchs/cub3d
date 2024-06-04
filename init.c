#include "includes/cub3d.h"

t_cub3d *init_cube3d(void)
{
    t_cub3d *cub3d;

    cub3d = malloc(sizeof(t_cub3d));
    if (!cub3d)
        return (NULL);
    cub3d->win_width = 480;
    cub3d->win_height = 480;
    cub3d->mlx = mlx_init();
    cub3d->win = mlx_new_window(cub3d->mlx, cub3d->win_width, cub3d->win_height, "Cub3D");
    cub3d->img = mlx_new_image(cub3d->mlx, cub3d->win_width, cub3d->win_height);
    cub3d->addr = mlx_get_data_addr(cub3d->img, &cub3d->bits_per_pixel, &cub3d->line_length, &cub3d->endian);
    cub3d->posX = 22;
    cub3d->posY = 12;
    cub3d->dirX = -1;
    cub3d->dirY = 0;
    cub3d->planeX = 0;
    cub3d->planeY = 0.66;
    cub3d->worldMap = malloc(sizeof(int *) * 24);
    return (cub3d);
    
}

t_data *init_data(void)
{
    t_data *data;

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

    return (data);
}  