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
		new_line[i] = (line[i] == ' ' ? '1' : line[i]);
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

char *print_tab(char **tab)
{
	int i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
	return (NULL);
}

// char	**dup_complete_map(char **map)


// char	**dup_complete_map(char **map)
// {
// 	int		longest_line;
// 	char	**new_map;
// 	int		i;

// 	if (!map)
// 		return (NULL);
// 	i = 0;
// 	// while (map[i][0] != '1' && map[i][0] != ' ')
// 		// i++;
// 	longest_line = get_longest_line(map);
// 	new_map = malloc(sizeof(char *) * (ft_tablen(map) + 1));
// 	while (i < ft_tablen(map))
// 	{
// 		new_map[i] = complete_line(map[i], longest_line);
// 		i++;
// 	}
// 	new_map[i] = NULL;
// 	printf("VOILA LA MAP\n");
// 	print_tab(new_map);
// 	return (new_map);
// }

int check_closing_conditions(char **map, int i, int j)
{
    // printf("Checking position (%d, %d)\n", i, j);
    if (i == 0 || i == ft_tablen(map) - 1
        || j == 0 || j == (int)ft_strlen(map[i]) - 1)
        return (0);
    if (map[i - 1][j] == '2' || map[i + 1][j] == '2'
        || map[i][j - 1] == '2' || map[i][j + 1] == '2')
        return (0);
    return (1);
}

int is_map_closed(t_data *data) {
    char **map;
    int i;
    int j;

    map = update_map(data, 0);
    // print_tab(map); // Affichez la carte pour le débogage
    if (!map)
        return (0);
    for (i = 0; map[i]; i++) {
        for (j = 0; map[i][j]; j++) {
            if (map[i][j] != '1') {
                if (!check_closing_conditions(map, i, j)) {
                    ft_exit(data, "Error\nMap is open\n");
                    free_tab((void **)map);
                    return (1);
                }
            }
        }
    }
    free_tab((void **)map);
    return (0);
}
