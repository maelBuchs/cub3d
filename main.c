/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:14:04 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/12 15:42:12 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void get_player_pos(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->cub3d->posx = j * 32 + 16;
				data->cub3d->posy = i * 32 + 16;
				if (data->map[i][j] == 'N')
				{
					data->cub3d->dirx = -1;
					data->cub3d->diry = 0;
					data->cub3d->planex = 0;
					data->cub3d->planey = 0.66;
				}
				else if (data->map[i][j] == 'S')
				{
					data->cub3d->dirx = 1;
					data->cub3d->diry = 0;
					data->cub3d->planex = 0;
					data->cub3d->planey = -0.66;
				}
				else if (data->map[i][j] == 'E')
				{
					data->cub3d->dirx = 0;
					data->cub3d->diry = 1;
					data->cub3d->planex = 0.66;
					data->cub3d->planey = 0;
				}
				else if (data->map[i][j] == 'W')
				{
					data->cub3d->dirx = 0;
					data->cub3d->diry = -1;
					data->cub3d->planex = -0.66;
					data->cub3d->planey = 0;
				}
			}
			j++;
		}
		i++;
	}

}

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
	is_map_closed(data);
	get_player_pos(data);
	
	// if (!is_map_closed(data)
		// ft_exit(data, "Error\nMap is not closed");
	
	// else
		// ft_exit(data, "No Error\nMap is closed");
	cub3d->win_height = 950;
	cub3d->win_width = 950;
	cub3d->mlx = mlx_init();
	cub3d->win = mlx_new_window(cub3d->mlx, cub3d->win_width, \
								cub3d->win_height, "Cub3D");
	cub3d->img = mlx_new_image(cub3d->mlx, cub3d->win_width, cub3d->win_height);
	cub3d->addr = mlx_get_data_addr(cub3d->img, &cub3d->bits_per_pixel,
									&cub3d->line_length, &cub3d->endian);
	init_textures(data);
	init_mlx(data, cub3d);
	free(data);
	free(cub3d);
	return (0);
}
