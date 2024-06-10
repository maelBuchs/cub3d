/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:28:06 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/09 16:24:16 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

// char *complete_line(char *line, int size)
// {
// 	char	*new_line;
// 	int		i;

// 	new_line = malloc(size + 1);
// 	i = 0;
// 	while (line[i])
// 	{
// 		new_line[i] = line[i];
// 		i++;
// 	}
// 	while (i < size)
// 	{
// 		new_line[i] = '0';
// 		i++;
// 	}
// 	new_line[i] = '\0';
// 	free(line);
// 	return (new_line);
// }

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

// void complete_map(t_data *data)
// {
// 	int i;
// 	int max_len;
	
// 	max_len = 0;
// 	i = 0;
// 	while(i < data->map_height)
// 	{
// 		if ((int)ft_strlen(data->map[i]) > max_len)
// 			max_len = ft_strlen(data->map[i]);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < data->map_height)
// 	{
// 		data->map[i] = complete_line(data->map[i], max_len);
// 		i++;
// 	}
// }
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
	// complete_map(data);
	return (data->map);
}
