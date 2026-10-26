/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:57 by svaladar          #+#    #+#             */
/*   Updated: 2026/10/26 20:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 * Registra os eventos da janela. O X (17), o par tecla-solta
 * (KeyPress = 2 sobe bandeira, KeyRelease = 3 desce) e o loop.
 * As mascaras 1L<<0 e 1L<<1 sao os bits do X11 de cada evento.
 */
static void	setup_hooks(t_scene *scene)
{
	mlx_hook(scene->mlx.win, 17, 1L << 17, close_hook, scene);
	mlx_hook(scene->mlx.win, 2, 1L << 0, key_press, scene);
	mlx_hook(scene->mlx.win, 3, 1L << 1, key_release, scene);
	mlx_loop_hook(scene->mlx.mlx, render_hook, scene);
}

static int	init_image(t_scene *scene)
{
	scene->mlx.img.ptr = mlx_new_image(scene->mlx.mlx, WIN_W, WIN_H);
	if (!scene->mlx.img.ptr)
		return (fail("mlx_new_image failed"));
	scene->mlx.img.addr = mlx_get_data_addr(scene->mlx.img.ptr,
			&scene->mlx.img.bpp, &scene->mlx.img.line_len,
			&scene->mlx.img.endian);
	return (1);
}

int	init_window(t_scene *scene)
{
	scene->mlx.mlx = mlx_init();
	if (!scene->mlx.mlx)
		return (fail("mlx_init failed"));
	scene->mlx.win = mlx_new_window(scene->mlx.mlx, WIN_W, WIN_H, "cub3D");
	if (!scene->mlx.win)
		return (fail("mlx_new_window failed"));
	if (!init_image(scene) || !load_textures(scene))
		return (0);
	setup_hooks(scene);
	return (1);
}
