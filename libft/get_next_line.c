/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbuchs <mael@buchs.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 10:16:43 by mbuchs            #+#    #+#             */
/*   Updated: 2023/11/26 10:16:43 by mbuchs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	stash_to_line(char *stash, char **line)
{
	int	i;
	int	len;

	len = 0;
	if (!ft_strlen(stash))
		return ;
	while (stash[len] && stash[len] != '\n')
		len++;
	if (stash[len] == '\n')
		len++;
	(*line) = malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		(*line)[i] = stash[i];
		i++;
	}
	if (stash[len] == '\n')
		(*line)[i] = stash[i];
	(*line)[len] = 0;
}
 
static int	check_stash(char *stash, int returned)
{
	int	i;

	i = 0;
	if (returned != BUFFER_SIZE)
		return (1);
	while (stash[i])
	{
		if (stash[i] == '\n' || stash[i] == 0)
			return (1);
		i++;
	}
	return (0);
}

static void	read_buffer(int fd, char **stash)
{
	int		returned;
	char	*buffer;

	returned = BUFFER_SIZE;
	while (!check_stash(*stash, returned))
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		returned = read(fd, buffer, BUFFER_SIZE);
		if (returned > 0)
		{
			buffer[returned] = 0;
			(*stash) = ft_strjoin((*stash), buffer);
		}
		else
			free(buffer);
	}
}

static char	*clean_stash(char *stash)
{
	int		i;
	int		j;
	char	*clean_stash;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	while (stash[j + i])
		j++;
	if (j == 0)
	{
		free(stash);
		return (NULL);
	}
	clean_stash = malloc(sizeof(char) * (j + 1));
	j = -1;
	while (stash[i + j++])
		clean_stash[j] = stash[j + i];
	free(stash);
	return (clean_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= 256)
		return (NULL);
	line = NULL;
	if (!stash)
		stash = ft_strdup("");
	read_buffer(fd, &stash);
	if (stash)
		stash_to_line(stash, &line);
	stash = clean_stash(stash);
	if (!line)
		return (NULL);
	return (line);
}