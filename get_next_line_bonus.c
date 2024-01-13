/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luciafe2 <luciafe2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:25:32 by luciafe2          #+#    #+#             */
/*   Updated: 2024/01/08 11:44:24 by luciafe2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_line(int fd, char *backup)
{
	int		bytes_read;
	char	*buffer;

	bytes_read = 0;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(backup, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buffer), NULL);
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		backup = ft_joinandfree(backup, buffer);
	}
	free(buffer);
	return (backup);
}

char	*extract_line(char *backup)
{
	char	*line;
	int		i;

	i = 0;
	if (backup[i] == '\0')
		return (NULL);
	while (backup[i] != '\n' && backup[i] != '\0')
		i ++;
	if (backup[i] == '\n')
		i ++;
	line = ft_substr (backup, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

char	*next_line(char *backup)
{
	char	*new_backup;
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (!backup)
		return (NULL);
	while (backup[count] != '\n' && backup[count] != '\0')
		count ++;
	if (backup[count] == '\0')
		return (free (backup), NULL);
	count ++;
	new_backup = (char *)malloc(ft_strlen(backup) - count + 1);
	if (!new_backup)
		return (free(backup), NULL);
	while (backup[count] != '\0')
	{
		new_backup[i] = backup[count];
		i ++;
		count ++;
	}
	free(backup);
	new_backup[i] = '\0';
	return (new_backup);
}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (backup[fd])
		{
			free(backup[fd]);
			backup[fd] = NULL;
		}
		return (NULL);
	}
	backup[fd] = read_line(fd, backup[fd]);
	if (!backup[fd])
		return (NULL);
	line = extract_line(backup[fd]);
	backup[fd] = next_line(backup[fd]);
	return (line);
}
