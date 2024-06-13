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
	t_ray	ray;

	initializeray(data, angle, &ray);
	dda(data, &ray);
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
