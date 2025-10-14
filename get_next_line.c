/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldinc <aldinc@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:44:38 by aldinc            #+#    #+#             */
/*   Updated: 2025/10/14 15:03:08 by aldinc           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Satırı ayıklar ve storage'ı bir sonraki çağrı için günceller.
static char	*ft_process_storage(char **storage)
{
	char	*line;
	char	*new_storage;
	char	*newline_ptr;
	int		len;

	newline_ptr = ft_strchr(*storage, '\n');
	if (newline_ptr)
	{
		len = (newline_ptr - *storage) + 1;
		line = (char *)malloc(sizeof(char) * (len + 1));
		if (!line)
			return (NULL);
		for (int i = 0; i < len; i++)
			line[i] = (*storage)[i];
		line[len] = '\0';
		
		new_storage = (char *)malloc(sizeof(char) * (ft_strlen(*storage) - len + 1));
		if (!new_storage)
		{
			free(line);
			return (NULL);
		}
		for (int i = 0, j = len; (*storage)[j]; i++, j++)
			new_storage[i] = (*storage)[j];
		new_storage[ft_strlen(*storage) - len] = '\0';
	}
	else // Dosyanın sonunda \n yoksa
	{
		line = *storage;
		*storage = NULL;
		return (line);
	}
	free(*storage);
	*storage = new_storage;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(storage);
			storage = NULL;
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		storage = ft_strjoin(storage, buffer);
		if (!storage)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	if (!storage || *storage == '\0')
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	return (ft_process_storage(&storage));
}
