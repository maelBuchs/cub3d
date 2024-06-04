/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:28:06 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/04 18:42:17 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	ft_strlen_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	ft_check_3D_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '2')
			{
				printf("Sprite found at %d %d\n", i, j);
				data->map_x = i;
				data->map_y = j;
			}
			j++;
		}
		i++;
	}
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == ' ');
}

int	is_valid_map_line(char *line)
{
	while (*line)
	{
		if (!is_valid_char(*line))
			return (0);
		line++;
	}
	return (1);
}

void	flood_fill(t_data *data, int x, int y, int *is_closed)
{
	// if (x < 0 || y < 0 || !data->map[y] || data->map[y][x] == '\0')
	// {
	// 	*is_closed = 0;
	// 	return ;
	// }
	x = 0;
	y = 0;
	if (data->map[y][x] == '1' || data->map[y][x] == '1')
		return ;
	flood_fill(data, x + 1, y, is_closed);
	flood_fill(data, x - 1, y, is_closed);
	flood_fill(data, x, y + 1, is_closed);
	flood_fill(data, x, y - 1, is_closed);
	printf("x = %d, y = %d\n", x, y);
}

int	is_map_closed(t_data *data, int player_x, int player_y)
{
	int	is_closed;

	is_closed = 1;
	flood_fill(data, player_x, player_y, &is_closed);
	return (is_closed);
}

int	split_map(t_data *data, char *str)
{
	int	i;
	int	len;

	i = 0;
	data->map = ft_split(str, '\n');
	if (!data->map || !data->map[0])
	{
		printf("Error\nFailed to split map\n");
		return (0);
	}
	len = ft_strlen_char(data->map[0], '\0');
	if (str)
	{
		free(str);
		str = NULL;
	}
	if (len < 2)
	{
		printf("Error\nMap is too small\n");
		return (0);
	}
	while (data->map[i])
	{
		if (!is_valid_map_line(data->map[i]) || (ft_strlen_char(data->map[i],
					'\0') != len))
		{
			printf("Error\nMap is not rectangular or contains invalid characters at line%d\n", i);
			return (0);
		}
		i++;
	}
	if (!is_map_closed(data, data->map_x, data->map_y))
	{
		printf("Error\nMap is not closed\n");
		return (0);
	}
	else
	{
		printf("Map is closed\n");
		printf("data->map_x = %d\n", data->map_x);
		printf("data->map_y = %d\n", data->map_y);

	}
	return (1);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*array;
	int		lenght;

	if (!s1 || !s2)
		return (NULL);
	lenght = (ft_strlen((char *)s1)) + (ft_strlen((char *)s2) + 1);
	array = ft_calloc(lenght, sizeof(char));
	if (!array)
		return (NULL);
	ft_strlcat(array, (char *)s1, lenght);
	ft_strlcat(array, (char *)s2, lenght);
	if (s1)
		free(s1);
	return (array);
}

void	parse_texture(t_data *data, char *line)
{
    (void)data;
    (void)line;
}

void	parse_color(t_data *data, char *line)
{
	(void)data;
	(void)line;
}

void	parse_element(t_data *data, char *line)
{
	if (strncmp(line, "NO ", 3) == 0)
		parse_texture(data, line);
	else if (strncmp(line, "SO ", 3) == 0)
		parse_texture(data, line);
	else if (strncmp(line, "WE ", 3) == 0)
		parse_texture(data, line);
	else if (strncmp(line, "EA ", 3) == 0)
		parse_texture(data, line);
	else if (strncmp(line, "F ", 2) == 0)
		parse_color(data, line);
	else if (strncmp(line, "C ", 2) == 0)
		parse_color(data, line);
	else if (is_valid_map_line(line))
	{
		if (!split_map(data, line))
		{
			printf("Error\nFailed to split map\n");
		}
	}
}

int	read_map(char *path, t_data *data)
{
	int		fd;
	int		rd_l;
	char	buffer[101];
	char	*str;
	char	**lines;
	int		i;

	if (!path || ft_strlen(path) < 4 || strcmp(path + ft_strlen(path) - 4,
			".cub") != 0)
	{
		printf("Error\nInvalid file extension. Must be .cub\n");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (0);
	}
	str = ft_strdup("");
	if (!str)
	{
		close(fd);
		return (0);

	}
	while ((rd_l = read(fd, buffer, 100)) > 0)
	{
		buffer[rd_l] = 0;
		str = ft_strjoin_free(str, buffer);
		if (!str)
		{
			close(fd);
			return (0);
		}
		printf("%s\n", str);
	}
	close(fd);
	lines = ft_split(str, '\n');
	free(str);
	for (i = 0; lines[i]; i++)
	{
		parse_element(data, lines[i]);
	}
	if (!data->map)
	{
		printf("Error\nNo map found\n");
		return (0);
	}
	printf("data->map[0] = %s\n", data->map[0]);
	ft_check_3D_map(data);
	return (1);
}
