/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:03:36 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/22 02:52:03 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_data	*init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	return (data);
}

t_cub3d	*init_cube3d(void)
{
	t_cub3d	*cub3d;

	cub3d = ft_calloc(sizeof(t_cub3d), 1);
	if (!cub3d)
		return (NULL);
	cub3d->posx = -2;
	cub3d->posy = -2;
	cub3d->dirx = -1;
	cub3d->planey = 0.66;
	cub3d->dirx = -1;
	cub3d->planey = 0.66;
	return (cub3d);
}

void	init_texture(t_texture *texture)
{
	texture->x = 0;
	texture->y = 0;
	texture->no_txt = NULL;
	texture->so_txt = NULL;
	texture->we_txt = NULL;
	texture->ea_txt = NULL;
	texture->img_struct = NULL;
	texture->img_struct = malloc(sizeof(t_img));
	if (!texture->img_struct)
	{
		free(texture);
		return ;
	}
	ft_memset(texture->img_struct, 0, sizeof(t_img));
}

t_ray	*init_ray(void)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		return (NULL);
	return (ray);
}

t_img	*init_img(void)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	return (img);
}
