/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mael@buchs.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:07:38 by mbuchs            #+#    #+#             */
/*   Updated: 2023/11/03 18:07:38 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t size)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (size)
	{
		if (((unsigned char *)p1)[i] != ((unsigned char *)p2)[i])
		{
			res = (((unsigned char *)p1)[i]) - (((unsigned char *)p2)[i]);
			return (res);
		}
		i++;
		size--;
	}
	return (0);
}
