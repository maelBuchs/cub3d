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

void	InitializeRay(t_data *data, float angle, t_ray *ray)
{
	float	posX;
	float	posY;

	posX = data->cub3d->posX / 32.0;
	posY = data->cub3d->posY / 32.0;
	ray->dirX = cos(angle);
	ray->dirY = sin(angle);
	ray->mapX = (int)posX;
	ray->mapY = (int)posY;
	ray->deltaDistX = fabs(1 / ray->dirX);
	ray->deltaDistY = fabs(1 / ray->dirY);
	ray->drawStart = 0;
	ray->drawEnd = data->cub3d->win_height;
	ray->side = 0;
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - posX) * ray->deltaDistX;
	}
	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - posY) * ray->deltaDistY;
	}
}

int	dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (data->map[ray->mapY][ray->mapX] == '1')
			hit = 1;
	}
	return (hit);
}

float	calculate_distance(t_ray *ray, t_data *data)
{
	float	perpWallDist;
	float	posX;
	float	posY;

	posX = data->cub3d->posX / 32.0;
	posY = data->cub3d->posY / 32.0;
	if (ray->side == 0)
		perpWallDist = (ray->mapX - posX + (1 - ray->stepX) / 2) / ray->dirX;
	else
		perpWallDist = (ray->mapY - posY + (1 - ray->stepY) / 2) / ray->dirY;
	data->side = ray->side;
	return (perpWallDist);
}

float	trace_ray(t_data *data, float angle)
{
	t_ray	ray;

	InitializeRay(data, angle, &ray);
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
			draw_pixel(cub3d, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

void	draw_vertical_line(t_cub3d *cub3d, int x, int drawStart, int drawEnd,
		unsigned int color)
{
	while (drawStart < drawEnd)
	{
		draw_pixel(cub3d, x, drawStart, color);
		drawStart++;
	}
}

void	render_scene(t_data *data)
{
	unsigned int	color;
	t_cub3d			*cub3d;
	t_ray			*ray;

	int x, lineHeight;
	float cameraX, rayDirX, rayDirY, distance;
	cub3d = data->cub3d;
	ray = malloc(sizeof(t_ray));
	x = 0;
	while (x < cub3d->win_width)
	{
		cameraX = 2 * x / (float)cub3d->win_width - 1;
		rayDirX = cub3d->dirX + cub3d->planeX * cameraX;
		rayDirY = cub3d->dirY + cub3d->planeY * cameraX;
		distance = trace_ray(data, atan2(rayDirY, rayDirX));
		lineHeight = (int)(cub3d->win_height / distance);
		ray->drawStart = -lineHeight / 2 + cub3d->win_height / 2;
		if (ray->drawStart < 0)
			ray->drawStart = 0;
		ray->drawEnd = lineHeight / 2 + cub3d->win_height / 2;
		if (ray->drawEnd >= cub3d->win_height)
			ray->drawEnd = cub3d->win_height - 1;
		if (data->side == 0)
			color = 0x00FF0000;
		else
			color = 0x0000FF00;
		draw_vertical_line(cub3d, x, ray->drawStart, ray->drawEnd, color);
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}

void	grrr(t_data *data)
{
	clear_screen(data->cub3d);
	render_scene(data);
}
