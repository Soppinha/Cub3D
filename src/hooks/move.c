/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+  +#+           */
/*   Created: 2026/10/25 18:30:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/10/25 18:30:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_dir(t_scene *scene)
{
	t_player	*p;

	p = &scene->player;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	p->plane_x = -sin(p->angle) * PLANE_LEN;
	p->plane_y = cos(p->angle) * PLANE_LEN;
}

static void	try_move(t_scene *scene, double dx, double dy)
{
	t_player	*p;

	p = &scene->player;
	if (can_stand(scene, p->x + dx, p->y))
		p->x += dx;
	if (can_stand(scene, p->x, p->y + dy))
		p->y += dy;
}

void	init_player(t_scene *scene)
{
	t_player	*p;

	p = &scene->player;
	p->x = (double)scene->map.player_x + 0.5;
	p->y = (double)scene->map.player_y + 0.5;
	if (scene->map.player_dir == DIR_N)
		p->angle = 3 * PI / 2;
	else if (scene->map.player_dir == DIR_S)
		p->angle = PI / 2;
	else if (scene->map.player_dir == DIR_W)
		p->angle = PI;
	else
		p->angle = 0;
	p->mouse_dx = 0;
	p->last_time = 0;
	update_dir(scene);
}

void	update_player(t_scene *scene, double dt)
{
	t_player	*p;
	double		step;

	p = &scene->player;
	step = MOVE_SPEED * dt;
	if (p->keys[IDX_LEFT])
		p->angle -= ROT_SPEED * dt;
	if (p->keys[IDX_RIGHT])
		p->angle += ROT_SPEED * dt;
	if (p->keys[IDX_W])
		try_move(scene, p->dir_x * step, p->dir_y * step);
	if (p->keys[IDX_S])
		try_move(scene, -p->dir_x * step, -p->dir_y * step);
	if (p->keys[IDX_A])
		try_move(scene, p->dir_y * step, -p->dir_x * step);
	if (p->keys[IDX_D])
		try_move(scene, -p->dir_y * step, p->dir_x * step);
	if (p->mouse_dx)
	{
		p->angle += p->mouse_dx * MOUSE_SENS;
		p->mouse_dx = 0;
	}
	update_dir(scene);
}
