/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:33:42 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/20 18:27:07 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_path(t_data *data)
{
	if(data->cub3d->no_path)
		free(data->cub3d->no_path);
	if(data->cub3d->so_path)
		free(data->cub3d->so_path);
	if(data->cub3d->we_path)
		free(data->cub3d->we_path);
	if(data->cub3d->ea_path)
		free(data->cub3d->ea_path);
}

void	free_tab(void **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void destroy_textures(t_img *img, t_data *data)
{
	if (img->txt)
		free(img->txt);
	if (img->img)
		mlx_destroy_image(data->cub3d->mlx, img->img);
	free(img);
}

void	clear_textures(t_data *data)
{
	if (data->cub3d->no_img)
		destroy_textures(data->cub3d->no_img, data);
	if (data->cub3d->so_img)
		destroy_textures(data->cub3d->so_img, data);
	if (data->cub3d->we_img)
		destroy_textures(data->cub3d->we_img, data);
	if (data->cub3d->ea_img)
		destroy_textures(data->cub3d->ea_img, data);
}

int	ft_exit(t_data *data, char *str)
{
	if (data->map)
		if (data->map)
		free_tab((void **)data->map);
	if (data->cub3d->map)
		free_tab((void **)data->cub3d->map);
	if (data && data->cub3d)
		free_path(data);
	if (str)
		printf("%s", str);
	if (data->cub3d->img)
		mlx_destroy_image(data->cub3d->mlx, data->cub3d->img);
	clear_textures(data);
	if (data->cub3d->win)
		mlx_destroy_window(data->cub3d->mlx, data->cub3d->win);
	if (data->cub3d->mlx)
	{
		mlx_destroy_display(data->cub3d->mlx);
		free(data->cub3d->mlx);
	}	
	if (data && data->cub3d)
		free(data->cub3d);
	if (data)
		free(data);
	exit(0);
}
