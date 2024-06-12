/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:03:36 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/11 19:36:14 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->res_x = 0;
	data->res_y = 0;
	data->s_path = NULL;
	data->minimap = 0;
	data->turn_left = 0;
	data->turn_right = 0;
	data->stepx = 0;
	data->stepy = 0;
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
	cub3d->worldMap = malloc(sizeof(int *) * 24);
	return (cub3d);
}

void	move(t_data *d, t_ray *ray, float posx, float posy)
{
	posx = d->cub3d->posx / 32.0;
	posy = d->cub3d->posy / 32.0;
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - posx) * ray->deltadistx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - posy) * ray->deltadisty;
	}
}

void	initializeray(t_data *data, float angle, t_ray *ray)
{
	float	posx;
	float	posy;

	posx = data->cub3d->posx / 32.0;
	posy = data->cub3d->posy / 32.0;
	ray->dirx = cos(angle);
	ray->diry = sin(angle);
	ray->mapx = (int)posx;
	ray->mapy = (int)posy;
	ray->deltadistx = fabs(1 / ray->dirx);
	ray->deltadisty = fabs(1 / ray->diry);
	ray->drawstart = 0;
	ray->drawend = data->cub3d->win_height;
	ray->side = 0;
	move(data, ray, posx, posy);
}
