/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltouzali <ltouzali@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 15:44:01 by ltouzali          #+#    #+#             */
/*   Updated: 2024/06/16 19:50:11 by ltouzali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	fast_cos(float angle)
{
	float	angle2;

	angle2 = angle * angle;
	return (1 - angle2 / 2 + angle2 * angle2 / 24);
}

float	fast_sin(float angle)
{
	float	angle2;

	angle2 = angle * angle;
	return (angle - angle2 / 6 + angle2 * angle * angle2 / 120);
}
