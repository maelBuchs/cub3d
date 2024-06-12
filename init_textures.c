/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mbuchs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:34:24 by mbuchs            #+#    #+#             */
/*   Updated: 2024/06/12 17:58:27 by mbuchs           ###   ########.fr       */
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

int rgbtoint(char *line)
{
    int r;
    int g;
    int b;
    int i;

    i = 0;
    r = 0;
    g = 0;
    b = 0;
    while (line[i] && line[i] != ',')
    {
        r = r * 10 + line[i] - '0';
        i++;
    }
    i++;
    while (line[i] && line[i] != ',')
    {
        g = g * 10 + line[i] - '0';
        i++;
    }
    i++;
    while (line[i])
    {
        b = b * 10 + line[i] - '0';
        i++;
    }
	printf("f_color = %x \n", r * 256 * 256 + g * 256 + b);
    return (r * 256 * 256 + g * 256 + b);
}

void parse_map_lines(t_data *data)
//TODO: [] replace printf with ft_exit
{
    int i = 0;
    // int j;
    while (data->map[i])
    {
        // j = 0;
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
            printf("Error\nskibidigyat\n");
            if (data->cub3d->f_color != -1)
                printf("Error\nFloor color set more than 1 time\n");
            data->cub3d->f_color = rgbtoint(data->map[i] + 2);
        }
        else if (data->map[i][0] == 'C' && data->map[i][1] == ' ')
        {
            if (data->cub3d->c_color != -1)
                printf("Error\nCeiling color set more than 1 time\n");
            data->cub3d->c_color = rgbtoint(data->map[i] + 2);
        }
        // else
        //     while (data->map[i][j])
        //     {
        //         if (data->map[i][j] == '1' || data->map[i][j] == '0')
        //             return ;
        //         j++;
        //     }  
        i++;
    }
}

void init_mlx_images(t_data *data)
{
    t_cub3d *c3d;
    
    c3d = data->cub3d;
    c3d->no_img->img = mlx_xpm_file_to_image
		(c3d->mlx, c3d->no_path, &c3d->no_img->height, &c3d->no_img->width);
    // c3d->so_img->img = mlx_xpm_file_to_image
    //     (c3d->mlx, c3d->so_path, &c3d->so_img->height, &c3d->so_img->width);
    // c3d->we_img->img = mlx_xpm_file_to_image
    //     (c3d->mlx, c3d->we_path, &c3d->we_img->height, &c3d->we_img->width);
    // c3d->ea_img->img = mlx_xpm_file_to_image
    //     (c3d->mlx, c3d->ea_path, &c3d->ea_img->height, &c3d->ea_img->width);
    printf("no_path = %s\n", c3d->no_path);
    if (c3d->no_img->img == NULL || c3d->so_img == NULL
        || c3d->we_img == NULL || c3d->ea_img == NULL)
        printf("Error\nTexture file not found\n");
}

int init_textures(t_data *data)
//TODO [] ajouter strtrim
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
    if (data->cub3d->no_path == NULL || data->cub3d->so_path == NULL
        || data->cub3d->we_path == NULL || data->cub3d->ea_path == NULL
        || data->cub3d->f_color == -1 || data->cub3d->c_color == -1)
        printf("Error\nMissing texture or color\n");
    init_mlx_images(data);
    return 0;
}