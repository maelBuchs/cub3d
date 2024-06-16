/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:33:42 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/16 20:37:16 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void    free_map(t_data *data)
{
    while (data->map[data->map_height])
    {
        free(data->map[data->map_height]);
        data->map_height++;
    }
    free(data->map);
}

int	ft_exit(t_data *data, char *str)
{
	free_map(data);
    if (str)
        ft_putendl_fd(str, 1);
    mlx_destroy_image(data->cub3d->mlx, data->cub3d->img);
    mlx_destroy_window(data->cub3d->mlx, data->cub3d->win);
    mlx_destroy_display(data->cub3d->mlx);
    free(data->cub3d);
	exit(0);
}