/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:14:04 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/26 14:25:21 by ltouzali         ###   ########.fr       */
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
			if ((data->map[i][j] == 'N' || data->map[i][j] == 'S' \
			|| data->map[i][j] == 'E' || data->map[i][j] == 'W') && data->cub3d->posx == -2)
			{
				printf("je rentre\n");
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
			else if(data->map[i][j] == 'N' || data->map[i][j] == 'S' \
			|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				ft_exit(data, "Error\nMultiple player positions\n");
			else if (data->map[i][j] != '1' && data->map[i][j] != '0' && data->map[i][j] != '2' && data->map[i][j] != ' ')
				ft_exit(data, "Error\nInvalid character in map\n");
			j++;
		}
		i++;
	}
	printf("posx = %f\n", data->cub3d->posx);
	if (data->cub3d->posx == -2)
		ft_exit(data, "Error\nNo player position\n");
}

void free_data_and_cub3d(t_data *data, t_cub3d *cub3d)
{
    if (data->map)
        free_tab((void **)data->map);
    free(data);
    free(cub3d);
}
// TODO : ne pas check les lignes vides apres la map

char **update_map(t_data *data, int mode)
{
	int i;
	int j;
	int k = 0;
	int max_len;
	char *tmp;
	char **newtab;
	
	i = 0;
	while (data->map[i][0] != '1' && data->map[i][0] != ' ')
		i++;
	max_len = get_longest_line(&data->map[i]);
	newtab = ft_calloc(ft_tablen(data->map) - i + 1, sizeof(char *));
	while (data->map[i])
	{
		j = 0;
		tmp = ft_calloc(max_len + 1, sizeof(char));
		while (data->map[i][j] && j < max_len)
		{
			if (data->map[i][j] == ' ')
				tmp[j] = '1';
			else
				tmp[j] = data->map[i][j];
			// ft_exit(data, "nope\n");
			j++;
		}
		while(j < max_len)
		{
			if (mode == 1)
				tmp[j] = '1';
			else
				tmp[j] = '2';
			j++;
		}
		newtab[k] = tmp;
		i++;
		k++;
	}
	if (mode == 1)
		free_tab((void **)data->map);
	return (newtab);
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

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;
	t_data	*data;

	if (argc != 2)
		printf("Error\nWrong number of arguments\n");
	if (argc != 2)
		exit (1);
	if (check_extension(argv[1], ".cub") == 0)
		printf("Error\nWrong filename\n");
	if (check_extension(argv[1], ".cub") == 0)
		exit (1);
	data = init_data();
	cub3d = init_cube3d();
	data->cub3d = cub3d;
	read_map(argv[1], data);
	is_map_closed(data);
	cub3d->win_width = 1280;
	cub3d->win_height = 720;
	cub3d->mlx = mlx_init();
	cub3d->img = mlx_new_image(cub3d->mlx, cub3d->win_width, cub3d->win_height);
	init_textures(data, cub3d);
	data->map = update_map(data, 1);
	get_player_pos(data);
	cub3d->win = mlx_new_window(cub3d->mlx, cub3d->win_width, \
								cub3d->win_height, "Cub3D");
	if (!cub3d->img)
		ft_exit(data, "Error\nImage not created\n");
	cub3d->addr = mlx_get_data_addr(cub3d->img, &cub3d->bits_per_pixel, \
				&cub3d->line_length, &cub3d->endian);
	data->map = update_map(data, 1);
	get_player_pos(data);
	data->map_height = get_longest_line(data->map);
	data->map_width = (ft_tablen(data->map) - 1);
	init_mlx(data, cub3d);
	ft_exit(data, NULL);
	return (0);
}
