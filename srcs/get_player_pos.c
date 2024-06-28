/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 00:05:09 by mbuchs            #+#    #+#             */
/*   Updated: 2024/06/29 00:08:23 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_n_s(t_data *data, t_cub3d *cub3d, int i, int j)
{
	cub3d->posx = j * 32 + 16;
	cub3d->posy = i * 32 + 16;
	if (data->map[i][j] == 'N')
	{
		cub3d->dirx = -1;
		cub3d->diry = 0;
		cub3d->planex = 0;
		cub3d->planey = 0.66;
	}
	else if (data->map[i][j] == 'S')
	{
		cub3d->dirx = 1;
		cub3d->diry = 0;
		cub3d->planex = 0;
		cub3d->planey = -0.66;
	}
}

void	init_e_w(t_data *data, t_cub3d *cub3d, int i, int j)
{
	cub3d->posx = j * 32 + 16;
	cub3d->posy = i * 32 + 16;
	if (data->map[i][j] == 'E')
	{
		cub3d->dirx = 0;
		cub3d->diry = 1;
		cub3d->planex = 0.66;
		cub3d->planey = 0;
	}
	else if (data->map[i][j] == 'W')
	{
		cub3d->dirx = 0;
		cub3d->diry = -1;
		cub3d->planex = -0.66;
		cub3d->planey = 0;
	}
}

int	is_player(char c, int mode)
{
	if (mode == 0)
		return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
	else
		return (c != '1' && c != '0' && c != '2' && c != ' ');
}

void	update_player(t_data *data, int i, int j)
{
	data->cub3d->posx = j * 32 + 16;
	data->cub3d->posy = i * 32 + 16;
	init_n_s(data, data->cub3d, i, j);
	init_e_w(data, data->cub3d, i, j);
}

void	get_player_pos(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (is_player(data->map[i][j], 0) && data->cub3d->posx == -2)
				update_player(data, i, j);
			else if (is_player(data->map[i][j], 0))
				ft_exit(data, "Error\nMultiple player positions\n");
			else if (is_player(data->map[i][j], 1))
				ft_exit(data, "Error\nInvalid character in map\n");
			j++;
		}
		i++;
	}
	if (data->cub3d->posx == -2)
		ft_exit(data, "Error\nNo player position\n");
}
