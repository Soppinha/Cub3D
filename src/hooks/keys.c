/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+  +#+           */
/*   Created: 2026/10/25 18:30:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/10/25 18:30:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_index(int keycode)
{
	if (keycode == KEY_W)
		return (IDX_W);
	if (keycode == KEY_A)
		return (IDX_A);
	if (keycode == KEY_S)
		return (IDX_S);
	if (keycode == KEY_D)
		return (IDX_D);
	if (keycode == KEY_LEFT)
		return (IDX_LEFT);
	if (keycode == KEY_RIGHT)
		return (IDX_RIGHT);
	return (-1);
}

void	set_key_flag(int keycode, int value, t_scene *scene)
{
	int	idx;

	idx = key_index(keycode);
	if (idx >= 0)
		scene->player.keys[idx] = value;
}

int	key_press(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == KEY_ESC)
		cleanup(scene, 0);
	set_key_flag(keycode, 1, scene);
	return (0);
}

int	key_release(int keycode, void *param)
{
	set_key_flag(keycode, 0, (t_scene *)param);
	return (0);
}
