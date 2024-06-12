/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:48:27 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/12 17:57:32 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
		player_move(d, 2);
	if (d->right == 1)
		player_move(d, 3);
	if (d->turn_left == 1)
		rotate(d, angle);
	if (d->turn_right == 1)
		rotate(d, -angle);
	// if (d->minimap == 1)
		// ft_draw(d->cub3d, d);
	if (d->minimap == 1 && d->cub3d->no_img->img != NULL)
		// mlx_put_image_to_window(d->cub3d->mlx, d->cub3d->win, d->cub3d->no_img, 0, 0);
		mlx_put_image_to_window(d->cub3d->mlx, d->cub3d->win, d->cub3d->no_img->img, 0, 0);
	// if (d->minimap == 1)
		// set_player(d->cub3d, d);
	else
		grrr(d);
	return (0);
}
