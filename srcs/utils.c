/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 16:49:56 by mbuchs            #+#    #+#             */
/*   Updated: 2024/06/24 18:43:17 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*ft_strndup(char *src, int n)
{
	char	*dest;
	int		i;

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

int	ft_tablen(char **tab)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	set_ray(t_cub3d *cub3d, float angle, t_ray *ray, t_data *data)
{
	float	posx;
	float	posy;

	posx = cub3d->posx / 32.0;
	posy = cub3d->posy / 32.0;
	ray->dirx = cos(angle);
	ray->diry = sin(angle);
	ray->mapx = (int)posx;
	ray->mapy = (int)posy;
	ray->deltadistx = sqrt(1 + (ray->diry * ray->diry) \
					/ (ray->dirx * ray->dirx));
	ray->deltadisty = sqrt(1 + (ray->dirx * ray->dirx) \
					/ (ray->diry * ray->diry));
	ray->drawstart = 0;
	ray->drawend = cub3d->win_height;
	ray->side = 0;
	move(data, ray, posx, posy);
}

int	check_copy(char *line_copy, char *line)
{
	if (!line_copy)
	{
		perror("Error duplicating line");
		free(line);
		return (1);
	}
	return (0);
}
