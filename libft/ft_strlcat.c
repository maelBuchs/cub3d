/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mael@buchs.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:09:23 by mbuchs            #+#    #+#             */
/*   Updated: 2023/11/03 18:09:23 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if ((dst == NULL || src == NULL) && (size <= 0))
		return (i + j);
	while (dst[i] && i < size)
		i++;
	while (src[j] && size != 0 && i + j < size - 1)
	{
		dst[j + i] = src[j];
		j++;
	}
	if (i < size)
		dst[i + j] = 0;
	j = ft_strlen(src);
	return (i + j);
}
