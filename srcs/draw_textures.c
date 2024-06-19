/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:10:53 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/19 16:05:15 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_img *check_texture(t_ray *ray, t_cub3d *cub3d)
{
	if (ray->side == 0)
	{
		if (ray->dirx > 0)
			return (cub3d->ea_img);
		else
			return (cub3d->we_img);
	}
	else
	{
		if (ray->diry > 0)
			return (cub3d->so_img);
		else
			return (cub3d->no_img);
	}
}

inline int	compute_wall_texture(t_img *img, t_ray *ray, t_data *data)
{
	float	wallx;
	int tex_x;

	if (ray->side == 0)
		wallx = data->cub3d->posy + ray->distance * ray->diry;
	else
		wallx = data->cub3d->posx + ray->distance * ray->dirx;
	wallx -= floor(wallx);
	tex_x = (int)(wallx * (float)img->width);
	if ((ray->side == 0 && ray->dirx > 0) || (ray->side == 1 && ray->diry < 0))
		tex_x = img->width - tex_x - 1;
	return (tex_x);
}

int get_pixel_from_image(t_img *img, int x, int y)
{
    char    *data_addr;
    int     bpp;
    int     size_line;
    int     endian;

    data_addr = mlx_get_data_addr(img->img, &bpp, &size_line, &endian);
    return *(int*)(data_addr + (y * size_line + x * (bpp / 8)));
}

void	load_texture(t_img *img, int **texture)
{
	(*texture) = malloc(sizeof(int) * img->width * \
				img->height);
	if (!*texture)
		return ;
    int    x;
    int    y;

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

	tex_y = 0;
	step = 1.0 * img->height / ray->lineheight;
	y = ray->drawstart;
	texpos = (ray->drawstart - cub3d->win_height / 2 + ray->lineheight / 2) * step;
	while (y < ray->drawend)
	{
		tex_y = ((int)texpos & (img->height - 1));
		texpos += step;
		color = img->txt[img->width * tex_y + cub3d->tex_x];
		draw_pixel(cub3d, ray->x, y, color);
		y++;
	}
}
