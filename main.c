/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:14:04 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/03 21:14:19 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;
	t_data 	data;

	(void)argc;
	(void)argv;
	cub3d = (t_cub3d){0};
	cub3d.win_width = 100;
	cub3d.win_height = 100;
	read_map("map.cub", &data);
	//put_map_to_window(&cub3d, &data);
	ft_draw(&cub3d, data);

	return (0);
}
