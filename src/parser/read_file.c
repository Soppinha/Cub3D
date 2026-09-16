/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:40:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

static void	strip_newline(char *line)
{
	int	len;

	len = 0;
	while (line[len])
		len++;
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static char	**grow_lines(char **lines, char *line, int count)
{
	char	**fresh;
	int		i;

	fresh = malloc(sizeof(char *) * (count + 2));
	if (!fresh)
		return (NULL);
	i = 0;
	while (i < count)
	{
		fresh[i] = lines[i];
		i++;
	}
	fresh[count] = line;
	fresh[count + 1] = NULL;
	free(lines);
	return (fresh);
}

static char	**read_all_lines(int fd)
{
	char	**lines;
	char	*line;
	int		count;

	lines = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		lines = grow_lines(lines, line, count);
		if (!lines)
		{
			free(line);
			return (NULL);
		}
		count++;
		line = get_next_line(fd);
	}
	return (lines);
}

char	**read_file_lines(char *path)
{
	int		fd;
	char	**lines;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		fail("cannot open map file");
		return (NULL);
	}
	lines = read_all_lines(fd);
	close(fd);
	if (!lines)
	{
		fail("empty map file");
		return (NULL);
	}
	return (lines);
}

void	free_lines(char **lines)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (lines[i])
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}
