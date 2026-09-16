/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 20:10:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:10:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	rotate_player(t_player *p, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(angle) - p->plane_y * sin(angle);
	p->plane_y = old_plane_x * sin(angle) + p->plane_y * cos(angle);
}

void	move_player(t_scene *scene, double dt)
{
	double	speed;
	double	rot;

	speed = MOVE_SPEED * dt;
	rot = ROT_SPEED * dt;
	if (scene->keys.up)
		move_forward(scene, speed);
	if (scene->keys.down)
		move_forward(scene, -speed);
	if (scene->keys.left)
		move_strafe(scene, -speed);
	if (scene->keys.right)
		move_strafe(scene, speed);
	if (scene->keys.rot_left)
		rotate_player(&scene->player, -rot);
	if (scene->keys.rot_right)
		rotate_player(&scene->player, rot);
}
