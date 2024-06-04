#include "includes/cub3d.h"

t_cub3d *init_cube3d(void)
{
    t_cub3d *cub3d;

    cub3d = malloc(sizeof(cub3d));
    cub3d->win_width = 100;
    cub3d->win_height = 100;
    cub3d->mlx = mlx_init();
    cub3d->win = mlx_new_window(cub3d->mlx, cub3d->win_width, cub3d->win_height, "Cub3D");
    cub3d->img = mlx_new_image(cub3d->mlx, cub3d->win_width, cub3d->win_height);
    cub3d->addr = mlx_get_data_addr(cub3d->img, &cub3d->bits_per_pixel, &cub3d->line_length, &cub3d->endian);
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
    data->f_color = 0;
    data->c_color = 0;
    data->map = NULL;
    data->map_x = 0;
    data->map_y = 0;

    return (data);
}  