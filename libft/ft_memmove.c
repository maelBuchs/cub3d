/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mael@buchs.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:07:52 by mbuchs            #+#    #+#             */
/*   Updated: 2023/11/03 18:07:52 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*from;
	unsigned char	*to;

	if (!dest && !src)
		return (NULL);
	from = (unsigned char *)src;
	to = (unsigned char *)dest;
	i = 0;
	if (to > from)
	{
		while (n--)
			to[n] = from[n];
	}
	else
	{
		while (i < n)
		{
			to[i] = from[i];
			i++;
		}
	}
	return (dest);
}
