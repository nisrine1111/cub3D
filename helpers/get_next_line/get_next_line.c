/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouknan <abouknan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 03:25:35 by abouknan          #+#    #+#             */
/*   Updated: 2024/12/22 23:15:45 by abouknan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_and_append(int fd, char *buffer, char *storage)
{
	int		bytes_read;
	char	*temp_storage;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp_storage = storage;
		storage = gnl_strjoin(temp_storage, buffer);
		if (!storage)
			return (NULL);
		if (gnl_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read == -1)
		return (NULL);
	return (storage);
}

static char	*get_line(char **storage)
{
	char	*line;
	char	*new_storage;
	size_t	i;

	if (**storage == '\0')
		return (NULL);
	i = 0;
	while ((*storage)[i] != '\n' && (*storage)[i])
		i++;
	line = gnl_substr(*storage, 0, i + ((*storage)[i] == '\n'));
	if (!line)
		return (NULL);
	new_storage = gnl_substr(*storage, i + 1, gnl_strlen(*storage) - i);
	*storage = new_storage;
	if (**storage == '\0')
		*storage = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd == 1 || fd == 2)
		return (NULL);
	buffer = (char *)ft_malloc((size_t)(BUFFER_SIZE) + 1);
	if (!buffer)
		return (NULL);
	storage = read_and_append(fd, buffer, storage);
	if (!storage)
		return (NULL);
	line = get_line(&storage);
	return (line);
}
