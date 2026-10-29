/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosta-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 13:43:50 by lcosta-a          #+#    #+#             */
/*   Updated: 2025/08/19 16:36:11 by lcosta-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy_gnl(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

void	*ft_memmove_gnl(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d > s)
	{
		while (n--)
			d[n] = s[n];
	}
	else
		ft_memcpy_gnl(d, s, n);
	return (dest);
}

static char	*read_to_buffer(int fd, char **buffer)
{
	char	*temp;
	char	*buf;
	int		bytes;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!ft_strchr_gnl(*buffer, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buf[bytes] = '\0';
		temp = ft_strjoin_gnl(*buffer, buf);
		*buffer = temp;
	}
	free(buf);
	return (*buffer);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*newline;

	newline = ft_strchr_gnl(*buffer, '\n');
	if (newline)
	{
		line = malloc(newline - *buffer + 1 + 1);
		if (!line)
		{
			free(*buffer);
			*buffer = NULL;
			return (NULL);
		}
		ft_memcpy_gnl(line, *buffer, newline - *buffer +1);
		line[newline - *buffer +1] = '\0';
		ft_memmove_gnl(*buffer, newline + 1, ft_strlen_gnl(newline + 1) + 1);
	}
	else
	{
		line = ft_strdup_gnl(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[FD_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = ft_strdup_gnl("");
		if (!buffer[fd])
			return (NULL);
	}
	if (!read_to_buffer(fd, &buffer[fd]))
		return (NULL);
	line = extract_line(&buffer[fd]);
	if (!line || !*line)
		return (free(line), NULL);
	return (line);
}
