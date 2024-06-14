/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Raycasting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 15:11:36 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/10 15:13:16 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>


int    dda(t_data *data, t_ray *ray)
{
    int    hit;
    int    map_height;
    int    map_width;

    hit = 0;
    map_height = ft_tablen(data->map);
    map_width = get_longest_line(data->map);

    while (hit == 0)
    {
        if (ray->sidedistx < ray->sidedisty)
        {
            ray->sidedistx += ray->deltadistx;
            ray->mapx += ray->stepx;
            ray->side = 0;
        }
        else
        {
            ray->sidedisty += ray->deltadisty;
            ray->mapy += ray->stepy;
            ray->side = 1;
        }

        if (ray->mapx < 0 || ray->mapy < 0 || ray->mapx >= map_width || ray->mapy >= map_height)
            return (1);

        if (data->map[ray->mapy][ray->mapx] == '1')
            hit = 1;
        // draw_pixel(data->cub3d, ray->mapx, ray->mapy, 0x000000FF);
    }
    return (hit);
}

void	*check_texture(t_ray *ray, t_data *data)
{
	if (ray->side == 0)
	{
		if (ray->dirx > 0)
			return(data->cub3d->ea_img->img);
		else
			return(data->cub3d->we_img->img);
	}
	else
	{
		if (ray->diry > 0)
			return(data->cub3d->so_img->img);
		else
			return(data->cub3d->no_img->img);
	}
}

void	compute_wall_texture(t_texture *texture, t_ray *ray, t_data *data)
{
	texture = init_texture();
	float wallx;

	if (ray->side == 0)
		wallx = data->cub3d->posy + ray->distance * ray->diry;
	else
		wallx = data->cub3d->posx + ray->distance * ray->dirx;
	wallx -= floor(wallx);
	texture->x = (int)(wallx * (float)texture->txt->width);
	if (ray->side == 0 && ray->dirx > 0 && texture->x == texture->txt->width)
		texture->x = texture->txt->width - texture->x - 1;
}

void load_texture(t_data *data, t_texture text, int **texture)
{
	*texture = malloc(sizeof(int) * text.txt->width * text.txt->height);
	if (!*texture)
		ft_exit(data, "Error\nMalloc failed\n");
	mlx_get_data_addr(data->cub3d->no_img->img, &data->cub3d->bits_per_pixel, \
						&data->cub3d->line_length, &data->cub3d->endian);
}

void draw_texture(t_data *data, t_ray *ray, t_texture *texture)
{
	int y;
	int d;
	int color;

	y = ray->drawstart;
	while (y < ray->drawend)
	{
		d = y * 256 - data->cub3d->win_height * 128 + ray->lineheight * 128;
		texture->y = ((d * texture->txt->height) / ray->lineheight) / 256;
		color = texture->txt->txt[texture->txt->width * texture->y + texture->x];
		draw_pixel(data->cub3d, data->cub3d->win_width - 1 - ray->x, y, color);
		y++;
	}
}



float	calculate_distance(t_ray *ray, t_data *data)
{
	float	perpwalldist;
	float	posx;
	float	posy;

	posx = data->cub3d->posx / 32.0;
	posy = data->cub3d->posy / 32.0;
	if (ray->side == 0)
		perpwalldist = (ray->mapx - posx + (1 - ray->stepx) / 2) / ray->dirx;
	else
		perpwalldist = (ray->mapy - posy + (1 - ray->stepy) / 2) / ray->diry;
	data->side = ray->side;
	return (perpwalldist);
}

float	trace_ray(t_data *data, float angle)
{
	t_ray	ray = {0};
	t_texture	*texture = NULL;

	initializeray(data, angle, &ray);
	dda(data, &ray);
	check_texture(&ray, data);
	compute_wall_texture(texture, &ray, data);
	return (calculate_distance(&ray, data));
}

void	clear_screen(t_cub3d *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < cub3d->win_height)
	{
		x = 0;
		while (x < cub3d->win_width)
		{
			if (y < cub3d->win_height / 2)
				draw_pixel(cub3d, x, y, cub3d->c_color);
			else
				draw_pixel(cub3d, x, y, cub3d->f_color);
			x++;
		}
		y++;
	}
}
