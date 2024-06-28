/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:55:28 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/28 17:00:35 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_longest_line(char **map)
{
	int	i;
	int	longest_line;

	if (!map)
		return (0);
	i = 0;
	longest_line = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > longest_line)
			longest_line = ft_strlen(map[i]);
		i++;
	}
	return (longest_line);
}

char	*complete_line(char *line, int size)
{
	char	*new_line;
	int		i;

	new_line = ft_calloc(size + 1, sizeof(char));
	i = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			new_line[i] = '1';
		else
			new_line[i] = line[i];
		i++;
	}
	while (i < size)
	{
		new_line[i] = '2';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

// char	*print_tab(char **tab)
// {
// 	int	i;

// 	i = 0;
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	return (NULL);
// }

int	check_closing_conditions(char **map, int i, int j)
{
	if (i == 0 || i == ft_tablen(map) - 1
		|| j == 0 || j == (int)ft_strlen(map[i]) - 1)
	{
		free(map);
		return (0);
	}
	if (map[i - 1][j] == '2' || map[i + 1][j] == '2'
		|| map[i][j - 1] == '2' || map[i][j + 1] == '2')
	{
		free(map);
		return (0);
	}
	return (1);
}

int	is_map_closed(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	map = update_map(data, 0);
	if (!map)
		return (0);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] != '1' && map[i][j] != '2')
			{
				if (!check_closing_conditions(map, i, j))
				{
					ft_exit(data, "Error\nMap is open\n");
					free_tab((void **)map);
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	free_tab((void **)map);
	return (0);
}
