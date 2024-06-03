/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:53 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/03 21:15:16 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

// Function to draw a pixel on the image
void	draw_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	dst = cub3d->addr + (y * cub3d->line_length + x * (cub3d->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

// Function to initialize window and image
void	ft_draw(t_cub3d *cub3d, t_data data)
{
	int	x;
	int	y;

	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, cub3d->win_width, cub3d->win_height, "Cub3D");
	cub3d->img = mlx_new_image(cub3d->mlx, cub3d->win_width, cub3d->win_height);
	cub3d->addr = mlx_get_data_addr(cub3d->img, &cub3d->bits_per_pixel, &cub3d->line_length, &cub3d->endian);
	y = 0;
	while (y < cub3d->win_height)
	{
		x = 0;
		while (x < cub3d->win_width)
		{
			if (data.map[y / 10][x / 10] + 1 == '1')
				draw_pixel(cub3d, x, y, 0x00FF0000);
			else
				draw_pixel(cub3d, x, y, 0x00000000);
		y++;
		}
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
	mlx_loop(cub3d->mlx);
}

