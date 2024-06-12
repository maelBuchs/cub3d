/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:24 by mbuchs            #+#    #+#             */
/*   Updated: 2024/06/11 20:34:02 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void parse_map_lines(t_data *data)
{
    int i = 0;
    while (data->map[i])
    {
        if (data->map[i][0] == 'N' && data->map[i][1] == 'O')
            data->no_path = ft_strdup(data->map[i] + 3);
        else if (data->map[i][0] == 'S' && data->map[i][1] == 'O')
            data->so_path = ft_strdup(data->map[i] + 3);
        else if (data->map[i][0] == 'W' && data->map[i][1] == 'E')
            data->we_path = ft_strdup(data->map[i] + 3);
        else if (data->map[i][0] == 'E' && data->map[i][1] == 'A')
            data->ea_path = ft_strdup(data->map[i] + 3);
        else if (data->map[i][0] == 'F' && data->map[i][1] == ' ')
            data->f_color = ft_atoi(data->map[i] + 2);
        else if (data->map[i][0] == 'C' && data->map[i][1] == ' ')
            data->c_color = ft_atoi(data->map[i] + 2);
        i++;
    }
}

int init_textures(t_data *data)
{
    int img_width;
    int img_height;
    
    data->no_path = NULL;
    data->so_path = NULL;
    data->we_path = NULL;
    data->ea_path = NULL;
    data->f_color = -1;
    data->c_color = -1;
    parse_map_lines(data);
    if (data->no_path == NULL || data->so_path == NULL || data->we_path == NULL || data->ea_path == NULL || data->f_color == -1 || data->c_color == -1)
        return (1);
    // init mlx images
    printf("NO = %s\n", data->no_path);
    data->cub3d->no_img = mlx_xpm_file_to_image
		(data->cub3d->mlx, "imgs/NO.bmp", &img_height, &img_width);
    // mlx_xpm_file_to_image(data->cub3d->mlx, data->no_path, data->cub3d->no_img, &data->cub3d->no_width, &data->cub3d->no_height);
    return 0;
}