/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:28:06 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/27 16:09:37 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_map(char *line)
{
	return (line[0] == '1' || line[0] == '0' || line[0] == ' ');
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1')
		return (1);
	return (0);
}

int	read_file(int fd, t_data *data, size_t j)
{
	char	*line;
	char	*line_copy;
	int		is_in_map;
	int		is_empty;
	int		does_map;

	does_map = 0;
	is_in_map = 0;
	is_empty = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!does_map)
			does_map = check_line(line);
		is_in_map = check_line(line);
		if (!is_in_map)
			line = ft_strtrim(line, " ");
		line_copy = ft_strdup(line);
		if (!line_copy)
		{
			free(line);
			ft_exit(data, "Error\nDuplicating line failed\n");
		}
		if (is_empty && does_map && is_in_map)
			ft_exit(data, "Error\nEmpty line in map\n");
		is_empty = 0;
		if (does_map && ft_strlen(line_copy) < 2)
			is_empty = 1;
		free(line);
		j = 0;
		while (line_copy[j])
		{
			if (line_copy[j] == '\n')
				line_copy[j] = '\0';
			j++;
		}
		if (ft_strlen(line_copy) > 1 || is_in_map)
		{
			data->map_height++;
			ft_extand_tab(&data->map, line_copy);
		}
		else
			free(line_copy);
		line = get_next_line(fd);
	}
	if (!does_map)
		ft_exit(data, "Error\nNo map found or no walls\n");
	return (0);
}

char	**read_map(char *path, t_data *data)
{
	int		fd;
	size_t	i;
	size_t	j;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		ft_exit(data, "Error\nCan't open map file\n");
	j = 0;
	if (read_file(fd, data, j))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	if (!data->map)
		ft_exit(data, "Error\nEmpty map\n");
	i = 0;
	while (data->map[i])
	{
		if ((int)ft_strlen(data->map[i]) > data->map_width)
			data->map_width = (int)ft_strlen(data->map[i]);
		i++;
	}
	return (data->map);
}
