/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:53 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/05 21:03:55 by ltouzali         ###   ########.fr       */
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

int	ft_exit(t_data *data, char *str)
{
	printf("%s\n", str);
	free(str);
	free(data->cub3d);
	free(data);
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

void	trace_ray(t_data *data)
{
	float	X;
	float	Y;
	float	deltaX;
	float	deltaY;
	float	steps;
	float	x_increment;
	float	y_increment;
	int		i;

	X = data->cub3d->posX;
	Y = data->cub3d->posY;
	deltaX = data->cub3d->dirX;
	deltaY = data->cub3d->dirY;
	steps = fmax(fabs(deltaX), fabs(deltaY));
	x_increment = deltaX / steps;
	y_increment = deltaY / steps;
	i = 0;
	while (data->map[(int)Y / 32][(int)X / 32] != '1'
		&& i < data->cub3d->win_width)
	{
		draw_pixel(data->cub3d, X, Y, 0x00FF0000);
		X += x_increment;
		Y += y_increment;
		printf("X = %f, Y = %f\n", X, Y);
		i++;
	}
}

void	ft_draw(t_cub3d *cub3d, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
				draw_fat_pixel(cub3d, x, y, 0x00FF0000);
			else
				draw_fat_pixel(cub3d, x, y, 0x000FF000);
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
	while (x < cub3d->win_width)
	{
		y = 0;
		while (y < cub3d->win_height)
		{
			if (cub3d->posX - 4 < x && x < cub3d->posX + 4 && cub3d->posY
				- 4 < y && y < cub3d->posY + 4)
				draw_pixel(cub3d, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}
	trace_ray(data);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}

int	press_key(int keycode, void *data)
{
	printf("keycode = %d\n", keycode);
	if (keycode == 109 || keycode == 65289)
		((t_data *)data)->minimap = 1;
	if (keycode == 119)
		((t_data *)data)->up = 1;
	if (keycode == 115)
		((t_data *)data)->down = 1;
	if (keycode == 97)
		((t_data *)data)->left = 1;
	if (keycode == 100)
		((t_data *)data)->right = 1;
	if (keycode == 65307)
		ft_exit(data, ft_strdup("Exit"));
	return (0);
}
int	unpress_key(int keycode, void *data)
{
	if (keycode == 109 || keycode == 65289)
		((t_data *)data)->minimap = 0;
	if (keycode == 119)
		((t_data *)data)->up = 0;
	if (keycode == 115)
		((t_data *)data)->down = 0;
	if (keycode == 97)
		((t_data *)data)->left = 0;
	if (keycode == 100)
		((t_data *)data)->right = 0;
	return (0);
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

void	grrr(t_data *data)
{
	int		x;
	int		y;
	t_cub3d	*cub3d;

	cub3d = data->cub3d;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (y < data->map_height / 2)
				draw_fat_pixel(cub3d, x, y, 0x00FF0000);
			else
				draw_fat_pixel(cub3d, x, y, 0x000FF000);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}

int	update(t_data *d)
{
	float	angle;
	float	oldDirX;

	angle = -0.005;
	if (!d)
	{
		printf("Error\n");
		return (0);
	}
	if (d->up == 1)
	{
		if (d->cub3d->posX + d->cub3d->dirX < d->cub3d->win_width
			&& d->cub3d->posX + d->cub3d->dirX > 0)
			d->cub3d->posX += d->cub3d->dirX;
		if (d->cub3d->posY + d->cub3d->dirY < d->cub3d->win_height
			&& d->cub3d->posY + d->cub3d->dirY > 0)
			d->cub3d->posY += d->cub3d->dirY;
	}
	if (d->down == 1)
	{
		if (d->cub3d->posX - d->cub3d->dirX < d->cub3d->win_width
			&& d->cub3d->posX - d->cub3d->dirX > 0)
			d->cub3d->posX -= d->cub3d->dirX;
		if (d->cub3d->posY - d->cub3d->dirY < d->cub3d->win_height
			&& d->cub3d->posY - d->cub3d->dirY > 0)
			d->cub3d->posY -= d->cub3d->dirY;
	}
	if (d->left == 1)
	{
		oldDirX = d->cub3d->dirX;
		d->cub3d->dirX = d->cub3d->dirX * cos(angle) - d->cub3d->dirY
			* sin(angle);
		d->cub3d->dirY = oldDirX * sin(angle) + d->cub3d->dirY * cos(angle);
	}
	if (d->right == 1)
	{
		oldDirX = d->cub3d->dirX;
		d->cub3d->dirX = d->cub3d->dirX * cos(-angle) - d->cub3d->dirY
			* sin(-angle);
		d->cub3d->dirY = oldDirX * sin(-angle) + d->cub3d->dirY * cos(-angle);
	}
	// mlx_clear_window(d->cub3d->mlx, d->cub3d->win);
	if (d->minimap == 1)
	{
		ft_draw(d->cub3d, d);
		set_player(d->cub3d, d);
	}
	else
		grrr(d);
	return (0);
}
