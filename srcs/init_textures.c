/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:24 by mbuchs            #+#    #+#             */
/*   Updated: 2024/06/26 17:51:49 by ltouzali         ###   ########.fr       */
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
	i++;
	while (line[i++ + 1])
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

void	init_mlx_images(t_data *data)
{
	t_cub3d	*c3d;

	c3d = data->cub3d;
	c3d->no_img->img = mlx_xpm_file_to_image
		(c3d->mlx, data->cub3d->no_path, \
		&c3d->no_img->height, &c3d->no_img->width);
	c3d->so_img->img = mlx_xpm_file_to_image
		(c3d->mlx, data->cub3d->so_path, \
		&c3d->so_img->height, &c3d->so_img->width);
	c3d->we_img->img = mlx_xpm_file_to_image
		(c3d->mlx, data->cub3d->we_path, \
		&c3d->we_img->height, &c3d->we_img->width);
	c3d->ea_img->img = mlx_xpm_file_to_image
		(c3d->mlx, data->cub3d->ea_path, \
		&c3d->ea_img->height, &c3d->ea_img->width);
	if (c3d->no_img->img == NULL || c3d->so_img->img == NULL
		|| c3d->we_img->img == NULL || c3d->ea_img->img == NULL)
		ft_exit(data, "Invalid or missing texture(s)\n");
	load_texture(c3d->no_img, &c3d->no_img->txt);
	load_texture(c3d->so_img, &c3d->so_img->txt);
	load_texture(c3d->we_img, &c3d->we_img->txt);
	load_texture(c3d->ea_img, &c3d->ea_img->txt);
}

int	is_power_of(int n, int base)
{
	if (n == 0)
		return (0);
	while (n != 1)
	{
		if (n % base != 0)
			return (0);
		n = n / base;
	}
	return (1);
}

void	check_texture_size(t_data *data)
{
	t_cub3d	*c3d;

	c3d = data->cub3d;
	if (!is_power_of(c3d->no_img->width, 2) || \
		!is_power_of(c3d->no_img->height, 2)
		|| !is_power_of(c3d->so_img->width, 2) || \
		!is_power_of(c3d->so_img->height, 2)
		|| !is_power_of(c3d->we_img->width, 2) || \
		!is_power_of(c3d->we_img->height, 2)
		|| !is_power_of(c3d->ea_img->width, 2) || \
		!is_power_of(c3d->ea_img->height, 2))
		ft_exit(data, "Error\nTexture size must be a power of 2\n");
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
