/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:53 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/13 11:57:25 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_exit(t_data *data, char *str)
{
	printf("%s\n", str);
	free(str);
	if (data)
	{
		if (data->cub3d)
		{
			free(data->cub3d);
		}
		free(data);
	}
	exit(0);
	return (0);
}

void	draw_fat_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 32)
	{
		j = 0;
		while (j < 32)
		{
			if (i == 0 || i == 31 || j == 0 || j == 31)
				draw_pixel(cub3d, x * 32 + i, y * 32 + j, 0x00000000);
			else
				draw_pixel(cub3d, x * 32 + i, y * 32 + j, color);
			j++;
		}
		i++;
	}
}

float	ft_abs(float x)
{
	if (x < 0)
		return (-x);
	return (x);
}

void	draw_rays(t_data *data)
{
	float	player_angle;
	float	start_angle;
	float	angle_increment;

	player_angle = atan2(data->cub3d->diry, data->cub3d->dirx);
	start_angle = player_angle - (FOV / 2.0f) * (M_PI / 180.0f);
	angle_increment = (FOV / data->cub3d->win_width) * (M_PI / 180.0f);
	while (start_angle < player_angle + (FOV / 2.0f) * (M_PI / 180.0f))
	{
		trace_ray(data, start_angle);
		start_angle += angle_increment;
	}
}

void	init_mlx(t_data *data, t_cub3d *cub3d)
{
	mlx_loop_hook(cub3d->mlx, update, (void *)data);
	mlx_hook(cub3d->win, 2, 1L << 0, press_key, data);
	mlx_hook(cub3d->win, 3, 1L << 1, unpress_key, data);
	update(data);
	mlx_hook(cub3d->win, 17, 1L << 17, ft_exit, data);
	mlx_loop(cub3d->mlx);
}
