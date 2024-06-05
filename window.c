/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:53 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/05 17:00:08 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <math.h>

void	draw_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	dst = cub3d->addr + (y * cub3d->line_length + x * (cub3d->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

int	ft_exit(t_data *data, char *str)
{
	printf("%s\n", str);
	free(str);
	free(data->cub3d);
	free(data);
	exit(0);
	return (0);
}

int	check_key(int keycode, t_data *data)
{
	printf("Keycode: %d\n", keycode);
	if (keycode == 65307)
		ft_exit(data, ft_strdup("Exit"));
	return (0);
}

unsigned int	dda(t_data *data)
{
	while (data->map_x != data->map_x + data->cub3d->dirX)
	{
		if (data->sideDistX < data->sideDistY)
		{
			data->sideDistX += data->deltaDistX;
			data->map_x += data->stepX;
			data->side = 0;
		}
		else
		{
			data->sideDistY += data->deltaDistY;
			data->map_y += data->stepY;
			data->side = 1;
		}
		if (data->cub3d->worldMap[data->map_x][data->map_y] == '1')
			break ;
	}
	return (0);
}

void	ft_draw(t_cub3d *cub3d, t_data *data)
{
	int	x;
	int	y;
	x = 0;
	while (x < cub3d->win_width - 1)
	{
		y = 0;
		while (y < cub3d->win_height - 1)
		{
			if (data->map[y / 32][x / 32] == '1')
				draw_pixel(cub3d, x, y, 0x00FF0000);
			else
				draw_pixel(cub3d, x, y, 0x00000000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}


void set_player(t_cub3d *cub3d, t_data *data)
{
	int x;
	int y;
	(void)data;

	x = 0;
	while (x < cub3d->win_width)
	{
		y = 0;
		while (y < cub3d->win_height)
		{
			if (cub3d->posX - 5 < x && x < cub3d->posX + 5 \
				&& cub3d->posY - 5 < y && y < cub3d->posY + 5)
				{
					draw_pixel(cub3d, x, y, 0xFF0000FF);
				}
			else
				draw_pixel(cub3d, x, y, 0x00000000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win,\
							cub3d->img, 0, 0);
}

void init_mlx(t_data *data, t_cub3d *cub3d)
{
	//ft_draw(cub3d, data);
	printf("data->mlx = %p\n", data->cub3d->mlx);
	mlx_loop_hook(cub3d->mlx, update, (void *)data);
	mlx_key_hook(cub3d->win, check_key, data);
	mlx_hook(cub3d->win, 17, 1L << 17, ft_exit, data);
	mlx_loop(cub3d->mlx);
}

int update(void *data)
{
	t_data *d;
	(void) d;
	if (!data)
	{
		printf("Error\n");
		return (0);
	}
	d = (t_data *)data;
	mlx_clear_window(d->cub3d->mlx, d->cub3d->win);
	ft_draw(d->cub3d, d);
	set_player(d->cub3d, d);
	return (0);
}
