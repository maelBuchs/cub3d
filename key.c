/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:49:21 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/12 16:03:39 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	press_key(int keycode, void *data)
{
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
	if (keycode == 65361)
		((t_data *)data)->turn_left = 1;
	if (keycode == 65363)
		((t_data *)data)->turn_right = 1;
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
	if (keycode == 65361)
		((t_data *)data)->turn_left = 0;
	if (keycode == 65363)
		((t_data *)data)->turn_right = 0;
	return (0);
}

void	rotate(t_data *d, double angle)
{
	// double	magnitude;
	double	olddirx;
	double  oldplanex;

	olddirx = d->cub3d->dirx;
	d->cub3d->dirx = d->cub3d->dirx * cos(angle) - d->cub3d->diry * sin(angle);
	d->cub3d->diry = olddirx * sin(angle) + d->cub3d->diry * cos(angle);
	// magnitude = sqrt(d->cub3d->dirx * d->cub3d->dirx + d->cub3d->diry * d->cub3d->diry);
	oldplanex = d->cub3d->planex;
	d->cub3d->planex = d->cub3d->planex * cos(angle) - d->cub3d->planey * sin(angle);
	d->cub3d->planey = oldplanex * sin(angle) + d->cub3d->planey * cos(angle);
}

void	move_side(t_data *d, int dir)
{
	if (dir == 2)
	{
		if (d->cub3d->posx - d->cub3d->diry < d->cub3d->win_width
			&& d->cub3d->posx - d->cub3d->diry > 0)
			d->cub3d->posx -= d->cub3d->diry;
		if (d->cub3d->posy + d->cub3d->dirx < d->cub3d->win_height
			&& d->cub3d->posy + d->cub3d->dirx > 0)
			d->cub3d->posy += d->cub3d->dirx;
	}
	if (dir == 3)
	{
		if (d->cub3d->posx + d->cub3d->diry < d->cub3d->win_width
			&& d->cub3d->posx + d->cub3d->diry > 0)
			d->cub3d->posx += d->cub3d->diry;
		if (d->cub3d->posy - d->cub3d->dirx < d->cub3d->win_height
			&& d->cub3d->posy - d->cub3d->dirx > 0)
			d->cub3d->posy -= d->cub3d->dirx;
	}
}

void	player_move(t_data *d, int dir)
// up = 0 // down = 1 // left = 2 // right = 3
{
	if (dir == 0)
	{
		if (d->cub3d->posx + d->cub3d->dirx < d->cub3d->win_width
			&& d->cub3d->posx + d->cub3d->dirx > 0)
			d->cub3d->posx += d->cub3d->dirx;
		if (d->cub3d->posy + d->cub3d->diry < d->cub3d->win_height
			&& d->cub3d->posy + d->cub3d->diry > 0)
			d->cub3d->posy += d->cub3d->diry;
	}
	else if (dir == 1)
	{
		if (d->cub3d->posx - d->cub3d->dirx < d->cub3d->win_width
			&& d->cub3d->posx - d->cub3d->dirx > 0)
			d->cub3d->posx -= d->cub3d->dirx;
		if (d->cub3d->posy - d->cub3d->diry < d->cub3d->win_height
			&& d->cub3d->posy - d->cub3d->diry > 0)
			d->cub3d->posy -= d->cub3d->diry;
	}
	else
		move_side(d, dir);
}
