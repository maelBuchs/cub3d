/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:14:04 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/05 16:59:44 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;
	t_data	*data;

	(void)argc;
	(void)argv;
	cub3d = init_cube3d();
	data = init_data();
	data->cub3d = cub3d;
	read_map("map.cub", data);
	cub3d->win_height = data->map_height * 32;
	cub3d->win_width = data->map_width * 32;
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, cub3d->win_width, \
								cub3d->win_height, "Cub3D");
	cub3d->img = mlx_new_image(cub3d->mlx, cub3d->win_width, cub3d->win_height);
	cub3d->addr = mlx_get_data_addr(cub3d->img, &cub3d->bits_per_pixel,
									&cub3d->line_length, &cub3d->endian);
	init_mlx(data, cub3d);
	free(data);
	free(cub3d);
	return (0);
}
