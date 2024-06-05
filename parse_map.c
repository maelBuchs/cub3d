/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:28:06 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/05 21:04:12 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_noice(char *line)
{
	return (line[0] == '1' || line[0] == '0' || line[0] == ' ');
}

int	checK_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			i++;
		else if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_collumn(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			j++;
		else if (line[i] != ' ')
			return (0);
		i++;
	}
	return (j);
}

char	**read_map(char *path, t_data *data)
{
	int		fd;
	char	*lines;
	size_t	i;

	fd = open(path, O_RDONLY);
	lines = get_next_line(fd);
	while (lines)
	{
		data->map_height++;
		ft_extand_tab(&data->map, ft_strdup(lines));
		free(lines);
		lines = get_next_line(fd);
	}
	i = 0;
	while (data->map[i])
	{
		if ((int)ft_strlen(data->map[i]) > data->map_width)
			data->map_width = (int)ft_strlen(data->map[i]);
		i++;
	}
	return (data->map);
}
