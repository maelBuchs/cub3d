/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:41:13 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/12 22:03:36 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	dst = cub3d->addr + (y * cub3d->line_length + x * (cub3d->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	ft_draw(t_cub3d *cub3d, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y <= data->map_width)
	{
		x = 0;
		while (x < data->map_height)
		{
			printf("data->map[%d] = %s\n", y, data->map[y]);
			if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
				draw_fat_pixel(cub3d, x, y, 0x00000088);
			else
				draw_fat_pixel(cub3d, x, y, 0x0000FF00);
			x++;
		}
		y++;
	}
}

void	set_player(t_cub3d *cub3d, t_data *data)
{
	int	x;
	int	y;

	(void)data;
	x = 0;
	while (x < cub3d->win_width )
	{
		y = 0;
		while (y < cub3d->win_height)
		{
			if (cub3d->posx - 4 < x && x < cub3d->posx + 4 && cub3d->posy
				- 4 < y && y < cub3d->posy + 4)
				draw_pixel(cub3d, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}
	draw_rays(data);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}
