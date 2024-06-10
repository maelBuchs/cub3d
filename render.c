/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:11:38 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/10 18:35:32 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_vertical_line(t_cub3d *cub3d, int x, t_ray *ray)
{
	while (ray->drawstart < ray->drawend)
	{
		draw_pixel(cub3d, x, ray->drawstart, ray->color);
		ray->drawstart++;
	}
}

unsigned int	chose_color(t_data *data)
{
	if (data->side == 0)
		return (0x00FF0000);
	else
		return (0x0000FF00);
}

void	render_scene(t_data *data)
{
	t_cub3d			*cub3d;
	t_ray			*ray;
	float			camerax;

	cub3d = data->cub3d;
	ray = malloc(sizeof(t_ray));
	ray->x = 0;
	while (ray->x < cub3d->win_width)
	{
		camerax = 2 * ray->x / (float)cub3d->win_width - 1;
		ray->raydirx = cub3d->dirx + cub3d->planex * camerax;
		ray->raydiry = cub3d->diry + cub3d->planey * camerax;
		ray->distance = trace_ray(data, atan2(ray->raydiry, ray->raydirx));
		ray->lineheight = (int)(cub3d->win_height / ray->distance);
		ray->drawstart = -ray->lineheight / 2 + cub3d->win_height / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + cub3d->win_height / 2;
		if (ray->drawend >= cub3d->win_height)
			ray->drawend = cub3d->win_height - 1;
		ray->color = chose_color(data);
		draw_vertical_line(cub3d, ray->x, ray);
		ray->x++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}

void	grrr(t_data *data)
{
	clear_screen(data->cub3d);
	render_scene(data);
}
