/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 20:33:42 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/18 22:53:34 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
void free_path(t_data *data)
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

int	ft_exit(t_data *data, char *str)
{
	if (data->map)
		free_tab(data->map);
	if (data->cub3d->map)
		free_tab(data->cub3d->map);
	free_path(data);
	if (str)
		ft_putendl_fd(str, 1);
	mlx_destroy_image(data->cub3d->mlx, data->cub3d->img);
	if (data->cub3d->so_img && data->cub3d->so_img->img)
		mlx_destroy_image(data->cub3d->mlx, data->cub3d->so_img->img);
	if (data->cub3d->so_img)
		free(data->cub3d->so_img);
	if (data->cub3d->no_img && data->cub3d->no_img->img)
		mlx_destroy_image(data->cub3d->mlx, data->cub3d->no_img->img);
	if (data->cub3d->no_img)
		free(data->cub3d->no_img);
	if (data->cub3d->we_img && data->cub3d->we_img->img)
		mlx_destroy_image(data->cub3d->mlx, data->cub3d->we_img->img);
	if (data->cub3d->we_img)
		free(data->cub3d->we_img);
	if (data->cub3d->ea_img && data->cub3d->ea_img->img)
		mlx_destroy_image(data->cub3d->mlx, data->cub3d->ea_img->img);
	if (data->cub3d->ea_img)
		free(data->cub3d->ea_img);
	mlx_destroy_window(data->cub3d->mlx, data->cub3d->win);
	mlx_destroy_display(data->cub3d->mlx);
	free(data->cub3d);
	exit(0);
}
