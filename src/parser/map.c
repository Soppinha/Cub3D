/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	is_blank(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

static int	find_map_bounds(char **lines, int start, int *out_i, int *out_h)
{
	int	i;
	int	height;

	i = start;
	while (lines[i] && is_blank(lines[i]))
		i++;
	height = 0;
	while (lines[i + height] && !is_blank(lines[i + height]))
		height++;
	*out_i = i;
	*out_h = height;
	return (height != 0);
}

static int	fill_grid(t_map *map, char **lines, int start, int height)
{
	int	y;
	int	width;

	y = 0;
	width = 0;
	while (y < height)
	{
		map->grid[y] = ft_strdup(lines[start + y]);
		if (!map->grid[y])
			return (fail("malloc failed"));
		if (!validate_charset(map->grid[y])
			|| !find_player(map->grid[y], y, map))
			return (0);
		if ((int)ft_strlen(map->grid[y]) > width)
			width = (int)ft_strlen(map->grid[y]);
		y++;
	}
	map->width = width;
	return (1);
}

int	parse_map(char **lines, int start, t_map *map)
{
	int	i;
	int	height;

	if (!find_map_bounds(lines, start, &i, &height))
		return (fail("no map found"));
	map->grid = ft_calloc(height + 1, sizeof(char *));
	if (!map->grid)
		return (fail("no map found"));
	map->height = height;
	map->grid[height] = NULL;
	if (!fill_grid(map, lines, i, height))
		return (0);
	i += height;
	while (lines[i] && is_blank(lines[i]))
		i++;
	if (lines[i])
		return (fail("content after map"));
	if (!map->has_player)
		return (fail("no player in map"));
	return (1);
}

void	free_map(t_map *map)
{
	int	y;

	if (!map->grid)
		return ;
	y = 0;
	while (map->grid[y])
	{
		free(map->grid[y]);
		y++;
	}
	free(map->grid);
}
