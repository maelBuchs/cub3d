/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:48:27 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/29 00:16:44 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (1);
	return (0);
}

int	update(t_data *d)
{
	float	angle;

	angle = 0.00999;
	if (!d)
		return (0);
	if (d->up == 1)
		player_move(d, 0);
	if (d->down == 1)
		player_move(d, 1);
	if (d->left == 1)
		player_move(d, 3);
	if (d->right == 1)
		player_move(d, 2);
	if (d->turn_left == 1)
		rotate(d, -angle);
	if (d->turn_right == 1)
		rotate(d, angle);
	grrr(d, d->cub3d);
	return (0);
}

void	init_mlx_images(t_data *data)
{
	t_cub3d	*c3d;

	c3d = data->cub3d;
	c3d->no_img->img = mlx_xpm_file_to_image
		(c3d->mlx, data->cub3d->no_path, \
		&c3d->no_img->height, &c3d->no_img->width);
	c3d->so_img->img = mlx_xpm_file_to_image
		(c3d->mlx, data->cub3d->so_path, \
		&c3d->so_img->height, &c3d->so_img->width);
	c3d->we_img->img = mlx_xpm_file_to_image
		(c3d->mlx, data->cub3d->we_path, \
		&c3d->we_img->height, &c3d->we_img->width);
	c3d->ea_img->img = mlx_xpm_file_to_image
		(c3d->mlx, data->cub3d->ea_path, \
		&c3d->ea_img->height, &c3d->ea_img->width);
	if (c3d->no_img->img == NULL || c3d->so_img->img == NULL
		|| c3d->we_img->img == NULL || c3d->ea_img->img == NULL)
		ft_exit(data, "Invalid or missing texture(s)\n");
	load_texture(c3d->no_img, &c3d->no_img->txt);
	load_texture(c3d->so_img, &c3d->so_img->txt);
	load_texture(c3d->we_img, &c3d->we_img->txt);
	load_texture(c3d->ea_img, &c3d->ea_img->txt);
}

void	check_texture_size(t_data *data)
{
	t_cub3d	*c3d;

	c3d = data->cub3d;
	if (!is_power_of(c3d->no_img->width, 2) || \
		!is_power_of(c3d->no_img->height, 2)
		|| !is_power_of(c3d->so_img->width, 2) || \
		!is_power_of(c3d->so_img->height, 2)
		|| !is_power_of(c3d->we_img->width, 2) || \
		!is_power_of(c3d->we_img->height, 2)
		|| !is_power_of(c3d->ea_img->width, 2) || \
		!is_power_of(c3d->ea_img->height, 2))
		ft_exit(data, "Error\nTexture size must be a power of 2\n");
}
