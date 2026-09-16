/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 20:10:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:10:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir_vectors(t_player *p, t_dir dir)
{
	static const double	dx[4] = {0, 0, 1, -1};
	static const double	dy[4] = {-1, 1, 0, 0};
	static const double	px[4] = {0.66, -0.66, 0, 0};
	static const double	py[4] = {0, 0, 0.66, -0.66};

	p->dir_x = dx[dir];
	p->dir_y = dy[dir];
	p->plane_x = px[dir];
	p->plane_y = py[dir];
}

void	init_player(t_scene *scene)
{
	scene->player.pos_x = scene->map.player_x + 0.5;
	scene->player.pos_y = scene->map.player_y + 0.5;
	set_dir_vectors(&scene->player, scene->map.player_dir);
}
