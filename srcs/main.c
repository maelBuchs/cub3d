/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:14:04 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/29 18:11:36 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_data_and_cub3d(t_data *data, t_cub3d *cub3d)
{
	if (data)
	{
		if (data->map)
			free_tab((void **)data->map, 1);
		free(data);
	}
	if (cub3d)
		free(cub3d);
}

int	check_extension(char *str, char *ext)
{
	int	i;
	int	j;

	i = ft_strlen(str) - 1;
	j = ft_strlen(ext) - 1;
	while (j >= 0 && i >= 0)
	{
		if (str[i] != ext[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

void	start_check(int argc, char **argv)
{
	if (argc != 2)
		printf("Error\nWrong number of arguments\n");
	if (argc != 2)
		exit (1);
	if (check_extension(argv[1], ".cub") == 0)
		printf("Error\nWrong filename\n");
	if (check_extension(argv[1], ".cub") == 0)
		exit (1);
}

void	init_all(t_data **data, t_cub3d **cub3d, char **argv)
{
	(*data) = init_data();
	(*cub3d) = init_cub3d();
	(*data)->cub3d = (*cub3d);
	read_map(argv[1], (*data));
	is_map_closed(*data);
	(*cub3d)->win_width = 1280;
	(*cub3d)->win_height = 720;
	(*cub3d)->mlx = mlx_init();
	(*cub3d)->img = mlx_new_image((*cub3d)->mlx,
			(*cub3d)->win_width, (*cub3d)->win_height);
	init_textures((*data), (*cub3d));
	(*data)->map = update_map((*data), 1);
	get_player_pos(*data);
}

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;
	t_data	*data;

	cub3d = NULL;
	data = NULL;
	start_check(argc, argv);
	init_all(&data, &cub3d, argv);
	cub3d->win = mlx_new_window(cub3d->mlx, cub3d->win_width, \
								cub3d->win_height, "Cub3D");
	if (!cub3d->img)
		ft_exit(data, "Error\nImage not created\n");
	cub3d->addr = mlx_get_data_addr(cub3d->img, &cub3d->bits_per_pixel, \
				&cub3d->line_length, &cub3d->endian);
	data->map = update_map(data, 1);
	data->map_height = get_longest_line(data->map);
	data->map_width = (ft_tablen(data->map) - 1);
	init_mlx(data, cub3d);
	ft_exit(data, NULL);
	return (0);
}
