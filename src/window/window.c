/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:57 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:23:25 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_hooks(t_scene *scene)
{
	mlx_hook(scene->mlx.win, 17, 1L << 17, close_hook, scene);
	mlx_key_hook(scene->mlx.win, key_hook, scene);
	mlx_loop_hook(scene->mlx.mlx, render_hook, scene);
}

int	init_window(t_scene *scene)
{
	scene->mlx.mlx = mlx_init();
	if (!scene->mlx.mlx)
		return (fail("mlx_init failed"));
	scene->mlx.win = mlx_new_window(scene->mlx.mlx, WIN_W, WIN_H, "cub3D");
	if (!scene->mlx.win)
		return (fail("mlx_new_window failed"));
	scene->mlx.img.ptr = mlx_new_image(scene->mlx.mlx, WIN_W, WIN_H);
	if (!scene->mlx.img.ptr)
		return (fail("mlx_new_image failed"));
	scene->mlx.img.addr = mlx_get_data_addr(scene->mlx.img.ptr,
			&scene->mlx.img.bpp, &scene->mlx.img.line_len,
			&scene->mlx.img.endian);
	setup_hooks(scene);
	return (1);
}
