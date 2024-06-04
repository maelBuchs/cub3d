/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:14:04 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/04 18:53:21 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	main(int argc, char **argv)
{
	t_cub3d	*cub3d;
	t_data 	*data;

	(void)argc;
	(void)argv;
	data = init_data();
	cub3d = init_cube3d();

	read_map("map.cub", data);
	//put_map_to_window(&cub3d, &data);
	ft_draw(cub3d, data);
	free(data);
	free(cub3d);
	return (0);
}
