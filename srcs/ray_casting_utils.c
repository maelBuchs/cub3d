/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 19:57:02 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/19 15:33:02 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

float	trace_ray(t_data *data, float angle)
{
	t_ray		ray;

	ray = (t_ray){0};
	set_ray(data->cub3d, angle, &ray, data);
	dda(data, &ray);
	data->cub3d->actual_texture = check_texture(&ray, data->cub3d);
	data->cub3d->tex_x = compute_wall_texture(data->cub3d->actual_texture, &ray, data);
	// if (texture.img_struct)
		// free(texture.img_struct);
	return (calculate_distance(&ray, data));
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
