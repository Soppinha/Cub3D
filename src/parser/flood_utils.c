/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 19:45:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

char	padded_cell(t_map *map, int y, int x)
{
	if (y <= 0 || x <= 0 || y >= map->height + 1 || x >= map->width + 1)
		return (' ');
	if (x - 1 >= (int)ft_strlen(map->grid[y - 1]))
		return (' ');
	return (map->grid[y - 1][x - 1]);
}

int	is_walkable(char c)
{
	return (c == ' ' || c == '0' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W');
}

int	touches_void(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] != ' ' && is_walkable(map->grid[y][x])
				&& (padded_cell(map, y, x + 1) == ' '
					|| padded_cell(map, y + 2, x + 1) == ' '
					|| padded_cell(map, y + 1, x) == ' '
					|| padded_cell(map, y + 1, x + 2) == ' '))
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}
