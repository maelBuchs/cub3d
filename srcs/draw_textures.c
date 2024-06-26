/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:10:53 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/26 14:20:50 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <cub3d.h>

t_img	*check_texture(t_ray *ray, t_cub3d *cub3d)
{
	if (ray->side == 0 && ray->diry < 0)
	{
			return (cub3d->so_img);
	}
	else if (ray->side == 0 && ray->diry > 0)
	{
		return (cub3d->no_img);
	}
	else if (ray->side == 1 && ray->dirx < 0)
	{
		return (cub3d->we_img);
	}
	else
	{
		return (cub3d->ea_img);
	}
}

inline int	compute_wall_texture(t_img *img, t_ray *ray, t_cub3d *cub3d)
{
	float	wallx;
	int		tex_x;

	(void)cub3d;
	if (ray->side == 0)
		wallx = + ray->distance * ray->raydiry;
	else
		wallx =  + ray->distance * ray->raydirx;	
	printf("wallx: %f\n", wallx);
	wallx -= floor(wallx);
	tex_x = (int)(wallx * (float)img->width);
	if ((ray->side == 1 && ray->raydirx > 0) || \
		(ray->side == 0 && ray->raydiry < 0))
		tex_x = img->width - tex_x - 1;
	return (tex_x);
}

int	get_pixel_from_image(t_img *img, int x, int y)
{
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;

	data_addr = mlx_get_data_addr(img->img, &bpp, &size_line, &endian);
	return (*(int *)(data_addr + (y * size_line + x * (bpp / 8))));
}

void	load_texture(t_img *img, int **texture)
{
	int		x;
	int		y;

	(*texture) = malloc(sizeof(int) * img->width * \
				img->height);
	if (!*texture)
		return ;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			(*texture)[y * img->width + x] = get_pixel_from_image(img, x, y);
			x++;
		}
		y++;
	}
}

void	draw_texture(t_cub3d *cub3d, t_ray *ray, t_img *img)
{
	int		y;
	int		color;
	float	step;
	float	texpos;
	int		tex_y;

	ray->tex_x = compute_wall_texture(img, ray, cub3d);
	check_texture(ray, cub3d);
	step = (float)img->width / ray->lineheight;
	texpos = (float)(ray->drawstart - cub3d->win_height / 2 \
			+ ray->lineheight / 2) * step;
	y = ray->drawstart;
	while (y < ray->drawend)
	{
		tex_y = (int)texpos % img->height;
		texpos += step;
		color = (img->txt)[img->width * tex_y + ray->tex_x];
		if (check_texture(ray, cub3d) == cub3d->no_img && ray->side == 1)
			color = (color >> 1) & 8355711;
		draw_pixel(cub3d, ray->x, y, color);
		y++;
	}
}
