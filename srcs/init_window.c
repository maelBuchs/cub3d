/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:41:13 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/29 18:11:12 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	update_line(char *line, char **tmp, int mode, int max_len)
{
	int	j;

	j = 0;
	(*tmp) = ft_calloc(max_len + 1, sizeof(char));
	while (line[j] && j < max_len)
	{
		(*tmp)[j] = line[j];
		if (line[j] == ' ')
			(*tmp)[j] = '1';
		j++;
	}
	while (j++ < max_len)
	{
		(*tmp)[j] = '2';
		if (mode == 1)
			(*tmp)[j] = '1';
	}
}

char	**update_map(t_data *data, int mode)
{
	int		i;
	int		k;
	char	*tmp;
	char	**newtab;
	int		max_len;

	max_len = get_longest_line(data->map);
	tmp = NULL;
	i = 0;
	k = 0;
	while (data->map[i][0] != '1' && data->map[i][0] != ' ')
		i++;
	newtab = ft_calloc(ft_tablen(data->map) - i + 1, sizeof(char *));
	while (data->map[i])
	{
		update_line(data->map[i], &tmp, mode, max_len);
		newtab[k] = tmp;
		i++;
		k++;
	}
	if (mode == 1)
		free_tab((void **)data->map, 1);
	return (newtab);
}

void	draw_pixel(t_cub3d *cub3d, int x, int y, int color)
{
	char	*dst;

	dst = cub3d->addr + (y * cub3d->line_length + x * (cub3d->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	ft_draw(t_cub3d *cub3d, t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y <= data->map_width)
	{
		x = 0;
		while (x < data->map_height)
		{
			if (x < (int)ft_strlen(data->map[y]) && data->map[y][x] == '1')
				draw_fat_pixel(cub3d, x, y, 0x00000088);
			else
				draw_fat_pixel(cub3d, x, y, 0x0000FF00);
			x++;
		}
		y++;
	}
}

void	set_player(t_cub3d *cub3d, t_data *data)
{
	int	x;
	int	y;

	(void)data;
	x = 0;
	while (x < cub3d->win_width)
	{
		y = 0;
		while (y < cub3d->win_height)
		{
			if (cub3d->posx - 4 < x && x < cub3d->posx + 4 && cub3d->posy
				- 4 < y && y < cub3d->posy + 4)
				draw_pixel(cub3d, x, y, 0xFF0000FF);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}
