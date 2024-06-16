/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:03:36 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/16 20:13:02 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
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
	cub3d->posx = 100;
	cub3d->posy = 100;
	cub3d->dirx = -1;
	cub3d->diry = 0;
	cub3d->planex = 0;
	cub3d->planey = 0.66;
	cub3d->posx = 100;
	cub3d->posy = 100;
	cub3d->dirx = -1;
	cub3d->diry = 0;
	cub3d->planex = 0;
	cub3d->planey = 0.66;
	return (cub3d);
}

t_texture	*init_texture(void)
{
	t_texture	*texture;

	texture = ft_calloc(1, sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->img_struct = malloc(sizeof(t_img));
	return (texture);
}

t_ray	*init_ray(void)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		return (NULL);
	return (ray);
}

void	set_ray(t_cub3d *cub3d, float angle, t_ray *ray, t_data *data)
{
	float	posx;
	float	posy;

	posx = cub3d->posx / 32.0;
	posy = cub3d->posy / 32.0;
	ray->dirx = cos(angle);
	ray->diry = sin(angle);
	ray->mapx = (int)posx;
	ray->mapy = (int)posy;
	ray->deltadistx = fabs(1 / ray->dirx);
	ray->deltadisty = fabs(1 / ray->diry);
	ray->drawstart = 0;
	ray->drawend = cub3d->win_height;
	ray->side = 0;
	move(data, ray, posx, posy);
}