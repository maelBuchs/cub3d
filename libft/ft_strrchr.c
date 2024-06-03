/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mael@buchs.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:10:08 by mbuchs            #+#    #+#             */
/*   Updated: 2023/11/03 18:10:08 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	returned;

	returned = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			returned = i;
		i++;
	}
	if (s[i] == c)
		returned = i;
	if (returned >= 0)
		return ((char *)(s + returned));
	return (NULL);
}
