/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 19:00:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/10/29 19:00:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	near_center(int x)
{
	return (x - WIN_W / 2 < WIN_W / 4 && WIN_W / 2 - x < WIN_W / 4);
}

static void	check_warp(t_player *p, int x)
{
	if (near_center(x))
	{
		p->mouse_dx += x - WIN_W / 2;
		p->mouse_x = x;
		p->mouse_warp = 0;
		return ;
	}
	p->mouse_warp++;
	if (p->mouse_warp > 3)
	{
		p->mouse_x = x;
		p->mouse_warp = -1;
	}
}

static int	mouse_move(int x, int y, void *param)
{
	t_scene		*scene;
	t_player	*p;

	scene = (t_scene *)param;
	p = &scene->player;
	if (x == WIN_W / 2)
		return (0);
	if (p->mouse_warp > 0)
		check_warp(p, x);
	else
	{
		if (p->mouse_x >= 0)
			p->mouse_dx += x - p->mouse_x;
		p->mouse_x = x;
	}
	if (p->mouse_warp == 0 && (x < WIN_W / 8 || x > WIN_W * 7 / 8))
	{
		mlx_mouse_move(scene->mlx.mlx, scene->mlx.win, WIN_W / 2, y);
		p->mouse_warp = 1;
	}
	return (0);
}

static int	mouse_leave(void *param)
{
	((t_scene *)param)->player.mouse_x = -1;
	return (0);
}

void	init_mouse(t_scene *scene)
{
	scene->player.mouse_x = -1;
	scene->player.mouse_warp = 0;
	mlx_mouse_hide(scene->mlx.mlx, scene->mlx.win);
	mlx_hook(scene->mlx.win, 6, 1L << 6, mouse_move, scene);
	mlx_hook(scene->mlx.win, 8, 1L << 5, mouse_leave, scene);
}
