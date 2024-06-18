/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:24 by mbuchs            #+#    #+#             */
/*   Updated: 2024/06/18 19:42:29 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	rgbtoint(char *line)
{
	int	r;
	int	g;
	int	b;
	int	i;

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

void	check_path(char *line, char *str, char *path, t_data *data)
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
		if (path)
			ft_exit(data, "Error\nTexture path set more than 1 time\n");
		path = ft_strndup(line + i, ft_strlen(line + i));
	}
}




void	parse_map_lines(t_data *data)
//TODO: verif char invalid
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		check_path(data->map[i], "NO", data->cub3d->no_path, data);
		check_path(data->map[i], "SO", data->cub3d->so_path, data);
		check_path(data->map[i], "WE", data->cub3d->we_path, data);
		check_path(data->map[i], "EA", data->cub3d->ea_path, data);
		if (data->map[i][0] == 'F' && data->map[i][1] == ' ')
		{
			if (data->cub3d->f_color != -1)
				ft_exit(data, "Error\nFloor color set more than 1 time\n");
			data->cub3d->f_color = rgbtoint(data->map[i] + 2);
		}
		if (data->map[i][0] == 'C' && data->map[i][1] == ' ')
		{
			if (data->cub3d->c_color != -1)
				ft_exit(data, "Error\nCeiling color set more than 1 time\n");
			data->cub3d->c_color = rgbtoint(data->map[i] + 2);
		}
		i++;
	}
}

void	init_mlx_images(t_data *data)
{
	t_cub3d	*c3d;

	c3d = data->cub3d;
	c3d->no_img->img = mlx_xpm_file_to_image
		(c3d->mlx, c3d->no_path, &c3d->no_img->height, &c3d->no_img->width);
	c3d->so_img->img = mlx_xpm_file_to_image
		(c3d->mlx, c3d->so_path, &c3d->so_img->height, &c3d->so_img->width);
	c3d->we_img->img = mlx_xpm_file_to_image
		(c3d->mlx, c3d->we_path, &c3d->we_img->height, &c3d->we_img->width);
	c3d->ea_img->img = mlx_xpm_file_to_image
		(c3d->mlx, c3d->ea_path, &c3d->ea_img->height, &c3d->ea_img->width);
	if (c3d->no_img->img == NULL || c3d->so_img == NULL
		|| c3d->we_img == NULL || c3d->ea_img == NULL)
		printf("Error\nTexture file not found\n");
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
	{
		printf("Error\nTexture path or color not set\n");
		return (1);
	}
	init_mlx_images(data);
	return (0);
}
