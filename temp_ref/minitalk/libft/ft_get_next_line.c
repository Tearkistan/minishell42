/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolich <psmolich@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 10:51:38 by psmolich          #+#    #+#             */
/*   Updated: 2025/08/27 06:26:21 by psmolich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#define FAIL -1
#define SUCCESS 1

static void	ft_free_rest(char **rest, int fd)
{
	free(rest[fd]);
	rest[fd] = NULL;
}

static int	ft_add_to_rest(int fd, char **rest)
{
	char	*buff;
	char	*temp;
	int		r_bytes;

	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (FAIL);
	r_bytes = 1;
	while (!ft_strchr(rest[fd], '\n') && r_bytes > 0)
	{
		r_bytes = read(fd, buff, BUFFER_SIZE);
		if (r_bytes < 0)
			return (free(buff), FAIL);
		if (r_bytes == 0)
			break ;
		buff[r_bytes] = '\0';
		temp = ft_strjoin(rest[fd], buff);
		if (!temp)
			return (free(buff), FAIL);
		free(rest[fd]);
		rest[fd] = temp;
	}
	return (free(buff), SUCCESS);
}

static char	*ft_line(int fd, char **rest)
{
	char	*new_ptr;
	char	*line;
	char	*temp;
	int		len;

	new_ptr = ft_strchr(rest[fd], '\n');
	if (new_ptr)
		len = new_ptr - rest[fd] + 1;
	else
		len = ft_strlen(rest[fd]);
	line = ft_substr(rest[fd], 0, len);
	if (!line)
	{
		ft_free_rest(rest, fd);
		return (NULL);
	}
	temp = ft_strdup(rest[fd] + len);
	if (!temp)
	{
		ft_free_rest(rest, fd);
		return (free(line), NULL);
	}
	free(rest[fd]);
	rest[fd] = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*rest[MAX_FD];
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest[fd])
	{
		rest[fd] = ft_strdup("");
		if (rest[fd] == NULL)
			return (NULL);
	}
	if (ft_add_to_rest(fd, rest) == FAIL)
	{
		ft_free_rest(rest, fd);
		return (NULL);
	}
	if (!rest[fd] || !rest[fd][0])
	{
		ft_free_rest(rest, fd);
		return (NULL);
	}
	line = ft_line(fd, rest);
	if (line == NULL)
		ft_free_rest(rest, fd);
	return (line);
}
