/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mael@buchs.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:07:59 by mbuchs            #+#    #+#             */
/*   Updated: 2023/11/03 18:07:59 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*pos;

	pos = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		(*pos) = c;
		pos++;
		i++;
	}
	return (s);
}
