/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+  +#+           */
/*   Created: 2026/09/16 18:54:31 by svaladar          #+#    #+#             */
/*   Updated: 2026/10/26 20:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	now_sec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

int	close_hook(void *param)
{
	return (cleanup((t_scene *)param, 0));
}

int	render_hook(void *param)
{
	t_scene	*scene;
	double	now;
	double	dt;

	scene = (t_scene *)param;
	now = now_sec();
	dt = 0;
	if (scene->player.last_time > 0)
		dt = now - scene->player.last_time;
	if (dt > MAX_DT)
		dt = MAX_DT;
	scene->player.last_time = now;
	update_player(scene, dt);
	render_frame(scene);
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win,
		scene->mlx.img.ptr, 0, 0);
	return (0);
}
