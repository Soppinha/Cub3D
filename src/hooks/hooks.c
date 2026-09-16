/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:31 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:21:46 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_hook(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == KEY_ESC)
		cleanup(scene, 0);
	return (0);
}

int	close_hook(void *param)
{
	return (cleanup((t_scene *)param, 0));
}

int	render_hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win,
		scene->mlx.img.ptr, 0, 0);
	return (0);
}
