/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrubal-c <mrubal-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 13:54:53 by mrubal-c          #+#    #+#             */
/*   Updated: 2024/10/10 13:36:06 by mrubal-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*ft_subs_line_from_save(char *save)
{
	char	*newsave;
	char	*ptr;
	int		len;

	ptr = ft_strchr(save, '\n');
	if (!ptr)
	{
		newsave = NULL;
		return (ft_free(&save));
	}
	else
		len = (ptr - save) + 1;
	if (!save[len])
		return (ft_free(&save));
	newsave = ft_substr(save, len, ft_strlen(save) - len);
	ft_free(&save);
	if (!newsave)
		return (NULL);
	return (newsave);
}

char	*ft_get_line(char *save)
{
	char	*line;
	char	*ptr;
	int		len;

	ptr = ft_strchr(save, '\n');
	len = (ptr - save) + 1;
	line = ft_substr(save, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_read_till_n(int fd, char *save)
{
	int		readed;
	char	*buffer;

	readed = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (ft_free(&save));
	buffer[0] = '\0';
	while (readed > 0 && !ft_strchr(buffer, '\n'))
	{
		readed = read (fd, buffer, BUFFER_SIZE);
		if (readed > 0)
		{
			buffer[readed] = '\0';
			save = ft_strjoin_modded(save, buffer);
		}
	}
	free(buffer);
	if (readed == -1)
		return (ft_free(&save));
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save[1024];
	char		*line;

	if (fd < 0)
		return (NULL);
	if ((save[fd] && !ft_strchr(save[fd], '\n')) || !save[fd])
		save[fd] = ft_read_till_n(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = ft_get_line(save[fd]);
	if (!line)
		return (ft_free(&save[fd]));
	save[fd] = ft_subs_line_from_save(save[fd]);
	return (line);
}
