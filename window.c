/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:53 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/04 18:21:27 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	draw_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	dst = cub3d->addr + (y * cub3d->line_length + x * (cub3d->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	ft_draw(t_cub3d *cub3d, t_data data)
{
	int	x;
	int	y;

	(void)data;
	printf("Drawing\n");
	y = 0;
	while (y < cub3d->win_height)
	{
		x = 0;
		while (x < cub3d->win_width)
		{
			draw_pixel(cub3d, x, y, 0x00FF0000);
			x++;
		}
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
	mlx_loop(cub3d->mlx);
}

