/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mael@buchs.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:07:46 by mbuchs            #+#    #+#             */
/*   Updated: 2023/11/03 18:07:46 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t size)
{
	char		*d;
	const char	*s;

	s = source;
	d = destination;
	if (s == NULL && d == NULL)
		return (destination);
	while (size)
	{
		*d++ = *s++;
		size--;
	}
	return (destination);
}
