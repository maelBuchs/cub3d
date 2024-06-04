/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:53 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/04 19:40:36 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	draw_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;
	
	dst = cub3d->addr + (y * cub3d->line_length + x * (cub3d->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	ft_exit(t_data *data, char *str)
{
	(void)str;
	
	//free(data->cub3d);
	free(data);
	exit(0);
	return (0);
}

int    check_key(int keycode, t_data *data)
{
	printf("Keycode: %d\n", keycode);
    if (keycode == 65307)
        ft_exit(data, ft_strdup("Exit"));
    return (0);
}

unsigned int dda(t_data *data)
{
	while (data->map_x != data->map_x + data->cub3d->dirX)
	{
		if (data->sideDistX < data->sideDistY)
		{
			data->sideDistX += data->deltaDistX;
			data->map_x += data->stepX;
			data->side = 0;
			data->f_color = 0x0000FF00;
		}
		else
		{
			data->sideDistY += data->deltaDistY;
			data->map_y += data->stepY;
			data->side = 1;
		}
		if (data->cub3d->worldMap[data->map_x][data->map_y] == '1')
			break;
	}
	return (0);
}

void	ft_draw(t_cub3d *cub3d, t_data *data)
{
	int	x;
	int	y;
	x = 0;
	while (x < data->res_x)
	{
		y = 0;
		while (y < data->res_y)
		{
			if (data->map_x == '1')
			{
				dda(data);
				draw_pixel(cub3d, x, y, data->f_color);
			}
			else
				draw_pixel(cub3d, x, y, 0x0000FF00);
		}
		x++;
	}
	mlx_key_hook(cub3d->win, check_key, data);
	mlx_hook(cub3d->win, 17, 1L << 17, ft_exit, data);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
	mlx_loop(cub3d->mlx);
}

