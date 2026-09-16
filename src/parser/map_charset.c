/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_charset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 19:45:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static t_dir	dir_from_char(char c)
{
	if (c == 'N')
		return (DIR_N);
	if (c == 'S')
		return (DIR_S);
	if (c == 'E')
		return (DIR_E);
	return (DIR_W);
}

int	validate_charset(char *line)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!is_map_char(line[x]))
			return (fail("invalid character in map"));
		x++;
	}
	return (1);
}

int	find_player(char *line, int y, t_map *map)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (is_player_char(line[x]))
		{
			if (map->has_player)
				return (fail("multi players in map"));
			map->has_player = 1;
			map->player_x = x;
			map->player_y = y;
			map->player_dir = dir_from_char(line[x]);
		}
		x++;
	}
	return (1);
}
