/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 19:45:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

static int	check_texture(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int	check_textures(t_config *cfg)
{
	if (!check_texture(cfg->tex_n))
		return (fail("missing texture: NO"));
	if (!check_texture(cfg->tex_s))
		return (fail("missing texture: SO"));
	if (!check_texture(cfg->tex_w))
		return (fail("missing texture: WE"));
	if (!check_texture(cfg->tex_e))
		return (fail("missing texture: EA"));
	return (1);
}

static char	*skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

static char	*trim_dup(char *s)
{
	char	*start;
	int		len;

	start = skip_spaces(s);
	len = ft_strlen(start);
	while (len > 0 && (start[len - 1] == ' ' || start[len - 1] == '\t'))
		len--;
	if (len == 0)
		return (NULL);
	return (ft_substr(start, 0, len));
}

int	set_texture(char **slot, char *line, int id_len)
{
	char	*path;

	path = trim_dup(line + id_len);
	if (!path)
		return (fail("empty texture path"));
	if (*slot)
	{
		free(path);
		return (fail("duplicate texture identifier"));
	}
	*slot = path;
	return (1);
}
