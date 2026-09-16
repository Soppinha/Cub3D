/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 20:10:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:10:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_wall_at(t_map *map, double x, double y)
{
	int	ix;
	int	iy;

	ix = (int)x;
	iy = (int)y;
	if (iy < 0 || iy >= map->height || ix < 0)
		return (1);
	if (ix >= (int)ft_strlen(map->grid[iy]))
		return (1);
	return (map->grid[iy][ix] == '1');
}

static void	try_move(t_player *p, t_map *map, double dx, double dy)
{
	if (!is_wall_at(map, p->pos_x + dx, p->pos_y))
		p->pos_x += dx;
	if (!is_wall_at(map, p->pos_x, p->pos_y + dy))
		p->pos_y += dy;
}

void	move_forward(t_scene *scene, double dist)
{
	try_move(&scene->player, &scene->map,
		scene->player.dir_x * dist, scene->player.dir_y * dist);
}

void	move_strafe(t_scene *scene, double dist)
{
	try_move(&scene->player, &scene->map,
		-scene->player.dir_y * dist, scene->player.dir_x * dist);
}
