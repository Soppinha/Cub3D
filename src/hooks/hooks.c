/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:31 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:30:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_key(t_keys *keys, int keycode, int value)
{
	if (keycode == KEY_W)
		keys->up = value;
	if (keycode == KEY_S)
		keys->down = value;
	if (keycode == KEY_A)
		keys->left = value;
	if (keycode == KEY_D)
		keys->right = value;
	if (keycode == KEY_LEFT)
		keys->rot_left = value;
	if (keycode == KEY_RIGHT)
		keys->rot_right = value;
}

int	key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == KEY_ESC)
		cleanup(scene, 0);
	update_key(&scene->keys, keycode, 1);
	return (0);
}

int	key_release_hook(int keycode, void *param)
{
	update_key(&((t_scene *)param)->keys, keycode, 0);
	return (0);
}

int	close_hook(void *param)
{
	return (cleanup((t_scene *)param, 0));
}

int	render_hook(void *param)
{
	t_scene	*scene;
	double	dt;

	scene = (t_scene *)param;
	dt = get_delta_time(scene);
	move_player(scene, dt);
	render_frame(scene);
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win,
		scene->mlx.img.ptr, 0, 0);
	return (0);
}
