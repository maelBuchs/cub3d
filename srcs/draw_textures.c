/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:10:53 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/16 20:12:18 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*check_texture(t_ray *ray, t_cub3d *cub3d)
{
	if (ray->side == 0)
	{
		if (ray->dirx > 0)
			return (cub3d->ea_img->img);
		else
			return (cub3d->we_img->img);
	}
	else
	{
		if (ray->diry > 0)
			return (cub3d->so_img->img);
		else
			return (cub3d->no_img->img);
	}
}

void	compute_wall_texture(t_texture *texture, t_ray *ray, t_data *data)
{
	float	wallx;

	texture = init_texture();
	if (ray->side == 0)
		wallx = data->cub3d->posy + ray->distance * ray->diry;
	else
		wallx = data->cub3d->posx + ray->distance * ray->dirx;
	wallx -= floor(wallx);
	texture->x = (int)(wallx * (float)texture->img_struct->width);
	if (ray->side == 0 && ray->dirx > 0 && texture->x == \
		texture->img_struct->width)
		texture->x = texture->img_struct->width - texture->x - 1;
}

void	load_texture(t_cub3d *cub3d, t_texture text, int **texture)
{
	*texture = malloc(sizeof(int) * text.img_struct->width * \
				text.img_struct->height);
	if (!*texture)
		return ;
	mlx_get_data_addr(cub3d->no_img->img, &cub3d->bits_per_pixel,
		&cub3d->line_length, &cub3d->endian);
}

void	draw_texture(t_cub3d *cub3d, t_ray *ray, t_texture *texture)
{
	int	y;
	int	d;
	int	color;

	y = ray->drawstart;
	while (y < ray->drawend)
	{
		d = y * 256 - cub3d->win_height * 128 + ray->lineheight * 128;
		texture->y = ((d * texture->img_struct->height) / \
						ray->lineheight) / 256;
		color = texture->img_struct->txt[texture->img_struct->width * texture->y
			+ texture->x];
		draw_pixel(cub3d, cub3d->win_width - 1 - ray->x, y, color);
		y++;
	}
}
