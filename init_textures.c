/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:24 by mbuchs            #+#    #+#             */
/*   Updated: 2024/06/12 17:22:45 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char *ft_strndup(char *src, int n)
{
    char *dest;
    int i;

    dest = malloc(sizeof(char) * (n + 1));
    if (!dest)
        return (NULL);
    i = 0;
    while (src[i] && i < n)
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return (dest);
}

void parse_map_lines(t_data *data)
//TODO: [] replace printf with ft_exit
{
    int i = 0;
    int j;
    while (data->map[i])
    {
        j = 0;
        if (data->map[i][0] == 'N' && data->map[i][1] == 'O')
        {
            if (data->cub3d->no_path != NULL)
                printf("Error\nNO texture set more than 1 time\n");
            data->cub3d->no_path = ft_strndup(data->map[i] + 3, ft_strlen(data->map[i] + 3) - 1);
        }
        else if (data->map[i][0] == 'S' && data->map[i][1] == 'O')
        {
            if (data->cub3d->so_path != NULL)
                printf("Error\nSO texture set more than 1 time\n");
            data->cub3d->so_path = ft_strndup(data->map[i] + 3, ft_strlen(data->map[i] + 3) - 1);
        }
        else if (data->map[i][0] == 'W' && data->map[i][1] == 'E')
        {
            if (data->cub3d->we_path != NULL)
                printf("Error\nWE texture set more than 1 time\n");
            data->cub3d->we_path = ft_strndup(data->map[i] + 3, ft_strlen(data->map[i] + 3) - 1);
        }
        else if (data->map[i][0] == 'E' && data->map[i][1] == 'A')
        {
            if (data->cub3d->ea_path != NULL)
                printf("Error\nEA texture set more than 1 time\n");
            data->cub3d->ea_path = ft_strndup(data->map[i] + 3, ft_strlen(data->map[i] + 3) - 1);
        }
        else if (data->map[i][0] == 'F' && data->map[i][1] == ' ')
        {
            if (data->cub3d->f_color != -1)
                printf("Error\nFloor color set more than 1 time\n");
            data->cub3d->f_color = ft_atoi(data->map[i] + 2);
        }
        else if (data->map[i][0] == 'C' && data->map[i][1] == ' ')
        {
            if (data->cub3d->c_color != -1)
                printf("Error\nCeiling color set more than 1 time\n");
            data->cub3d->c_color = ft_atoi(data->map[i] + 2);
        }
        else
            while (data->map[i][j])
            {
                if (data->map[i][j] == '1' || data->map[i][j] == '0')
                    return ;
                j++;
            }  
        i++;
    }
}

void init_mlx_images(t_data *data)
{
    data->cub3d->no_img = mlx_xpm_file_to_image
		(data->cub3d->mlx, data->cub3d->no_path, &data->cub3d->no_img->height, &data->cub3d->no_img->width);
    data->cub3d->so_img = mlx_xpm_file_to_image
        (data->cub3d->mlx, data->cub3d->so_path, &data->cub3d->so_img->height, &data->cub3d->so_img->width);
    data->cub3d->we_img = mlx_xpm_file_to_image
        (data->cub3d->mlx, data->cub3d->we_path, &data->cub3d->we_img->height, &data->cub3d->we_img->width);
    data->cub3d->ea_img = mlx_xpm_file_to_image
        (data->cub3d->mlx, data->cub3d->ea_path, &data->cub3d->ea_img->height, &data->cub3d->ea_img->width);
    if (data->cub3d->no_img == NULL || data->cub3d->so_img == NULL || data->cub3d->we_img == NULL || data->cub3d->ea_img == NULL)
        printf("Error\nTexture file not found\n");
}

int init_textures(t_data *data)
{
    data->cub3d->no_path = NULL;
    data->cub3d->so_path = NULL;
    data->cub3d->we_path = NULL;
    data->cub3d->ea_path = NULL;
    data->cub3d->f_color = -1;
    data->cub3d->c_color = -1;
    data->cub3d->ea_img = malloc(sizeof(t_img));
    data->cub3d->no_img = malloc(sizeof(t_img));
    data->cub3d->so_img = malloc(sizeof(t_img));
    data->cub3d->we_img = malloc(sizeof(t_img));
    
    parse_map_lines(data);
    if (data->cub3d->no_path == NULL || data->cub3d->so_path == NULL || data->cub3d->we_path == NULL || data->cub3d->ea_path == NULL || data->cub3d->f_color == -1 || data->cub3d->c_color == -1)
        printf("Error\nMissing texture or color\n");
    init_mlx_images(data);
    return 0;
}