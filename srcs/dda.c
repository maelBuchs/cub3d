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

int	check_dda(t_ray *ray, t_data *data)
{
	int	map_height;
	int	map_width;

	map_height = ft_tablen(data->map);
	map_width = get_longest_line(data->map);
	if (ray->mapx < 0 || ray->mapy < 0 || ray->mapx >= map_width
		|| ray->mapy >= map_height)
		return (1);
	if (data->map[ray->mapy][ray->mapx] == '1')
		return (1);
	return (0);
}

int	dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
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
		if (check_dda(ray, data))
			hit = 1;
	}
	return (hit);
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
