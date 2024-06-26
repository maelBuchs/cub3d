/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:24 by mbuchs            #+#    #+#             */
/*   Updated: 2024/07/01 22:02:03 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	check_rgb_input(char *line, t_data *data)
{
	int	i;
	int	comma;

	i = 0;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',' && (line[i + 1] < '0' || \
			line[i + 1] > '9') && line[i + 1] != ' ')
			ft_exit(data, "Error\nInvalid RGB color\n");
		if (line[i] == ',')
			comma++;
		if ((line[i] < '0' || line[i] > '9') && line[i] \
			!= ',' && line[i] != ' ')
			ft_exit(data, "Error\nInvalid RGB color\n");
		i++;
	}
	if (comma != 2)
		ft_exit(data, "Error\nInvalid RGB color\n");
}

int	rgbtoint(char *line, t_data *data)
{
	int	r;
	int	g;
	int	b;
	int	i;

	check_rgb_input(line, data);
	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (line[i] && line[i] != ',')
	{
		r = r * 10 + line[i] - '0';
		i++;
	}
	i++;
	while (line[i] && line[i] != ',')
	{
		g = g * 10 + line[i] - '0';
		i++;
	}
	while (line[1 + i++])
		b = b * 10 + line[i] - '0';
	return (r * 256 * 256 + g * 256 + b);
}

void	check_path(char *line, char *str, char **path, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] == str[j] && str[j])
	{
		i++;
		j++;
	}
	if (str[j] == '\0')
	{
		while (line[i] == ' ')
			i++;
		if ((*path))
			ft_exit(data, "Error\nTexture path set more than 1 time\n");
		(*path) = ft_strndup(line + i, ft_strlen(line + i));
	}
}

void	parse_map_lines(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		check_path(data->map[i], "NO", &data->cub3d->no_path, data);
		check_path(data->map[i], "SO", &data->cub3d->so_path, data);
		check_path(data->map[i], "WE", &data->cub3d->we_path, data);
		check_path(data->map[i], "EA", &data->cub3d->ea_path, data);
		if (data->map[i][0] == 'F' && data->map[i][1] == ' ')
		{
			if (data->cub3d->f_color != -1)
				ft_exit(data, "Error\nFloor color set more than 1 time\n");
			data->cub3d->f_color = rgbtoint(data->map[i] + 2, data);
		}
		if (data->map[i][0] == 'C' && data->map[i][1] == ' ')
		{
			if (data->cub3d->c_color != -1)
				ft_exit(data, "Error\nCeiling color set more than 1 time\n");
			data->cub3d->c_color = rgbtoint(data->map[i] + 2, data);
		}
		i++;
	}
}

int	init_textures(t_data *data, t_cub3d *cub3d)
{
	cub3d->no_path = NULL;
	cub3d->so_path = NULL;
	cub3d->we_path = NULL;
	cub3d->ea_path = NULL;
	cub3d->f_color = -1;
	cub3d->c_color = -1;
	cub3d->ea_img = ft_calloc(sizeof(t_img), 1);
	cub3d->no_img = ft_calloc(sizeof(t_img), 1);
	cub3d->so_img = ft_calloc(sizeof(t_img), 1);
	cub3d->we_img = ft_calloc(sizeof(t_img), 1);
	parse_map_lines(data);
	if (cub3d->no_path == NULL || cub3d->so_path == NULL
		|| cub3d->we_path == NULL || cub3d->ea_path == NULL
		|| cub3d->f_color == -1 || cub3d->c_color == -1)
		ft_exit(data, "Error\nMissing texture(s) or color(s)\n");
	init_mlx_images(data);
	check_texture_size(data);
	return (0);
}
