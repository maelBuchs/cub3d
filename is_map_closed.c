/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 16:00:23 by mbuchs            #+#    #+#             */
/*   Updated: 2024/06/09 16:29:43 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int ft_tablen(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i);
}

int get_longest_line(char **map)
{
    int i;
    int longest_line;

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

char *complete_line(char *line, int size)
{
    char *new_line;
    int i;

    new_line = malloc(size + 1);
    i = 0;
    while (line[i + 1])
    {
        new_line[i] = line[i];
        if (line[i] == ' ')
            new_line[i] = '1';
        i++;
    }
    while (i < size)
    {
        new_line[i] = '2';
        i++;
    }
    new_line[i] = '\0';
    free(line);
    return (new_line);
}

void print_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        printf("%s\n", tab[i]);
        i++;
    }
}

char **dup_complete_map(char **map)
{
    int longest_line;
    char **new_map;
    int i;
    
    i = 0;
    longest_line = get_longest_line(map);
    new_map = malloc(sizeof(char *) * (ft_tablen(map) + 1));
    while(i < ft_tablen(map))
    {
        new_map[i] = complete_line(map[i], longest_line);
        i++;
    }
    print_tab(new_map);
    return (new_map);
}

int is_map_closed(t_data *data)
{
    char **map;
    int i;
    int j;

    i = 0;
    map = dup_complete_map(data->map);
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (map[i][j] == '0')
            {
                if (i == 0 || i == ft_tablen(map) - 1 || j == 0 || j == (int) ft_strlen(map[i]) - 1)
                    return (0);
                if (map[i - 1][j] == '2' || map[i + 1][j] == '2' || map[i][j - 1] == '2' || map[i][j + 1] == '2')
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (1);
}