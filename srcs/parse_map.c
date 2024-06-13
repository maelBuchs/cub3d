/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:28:06 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/13 17:03:59 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	is_noice(char *line)
{
	return (line[0] == '1' || line[0] == '0' || line[0] == ' ');
}

int	check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_column(char *line)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '1')
			j++;
		else if (line[i] != ' ' && line[i] != '0')
			return (0);
		else if (line[i] == ' ')
			line[i] = '0';
		i++;
	}
	return (j);
}

int	read_file(int fd, t_data *data, size_t j)
{
	char	*lines;
	char	*line_copy;

	lines = get_next_line(fd);
	while (lines)
	{
		line_copy = ft_strdup(lines);
		if (!line_copy)
			perror("Error duplicating line");
		if (!line_copy)
			return (1);
		j = 0;
		while (line_copy[j++])
			if (line_copy[j] == '\n')
				line_copy[j] = '\0';
		if (ft_strlen(lines) > 1)
			data->map_height++;
		if (ft_strlen(lines) > 1)
			ft_extand_tab(&data->map, line_copy);
		free(lines);
		lines = get_next_line(fd);
	}
	return (0);
}

char	**read_map(char *path, t_data *data)
{
	int		fd;
	size_t	i;
	size_t	j;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (NULL);
	}
	j = 0;
	if (read_file(fd, data, j))
	{
		close(fd);
		return (NULL);
	}
	close(fd);
	i = 0;
	while (data->map[i])
	{
		if ((int)ft_strlen(data->map[i]) > data->map_width)
			data->map_width = (int)ft_strlen(data->map[i]);
		i++;
	}
	return (data->map);
}
