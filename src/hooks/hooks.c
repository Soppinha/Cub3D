/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+  +#+           */
/*   Created: 2026/09/16 18:54:31 by svaladar          #+#    #+#             */
/*   Updated: 2026/10/25 18:30:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Os hooks que o LOOP chama.
 *
 * key_press / key_release: moram no keys.c (as bandeiras).
 * close_hook: o X da janela.
 * render_hook: o coracao do jogo. A cada volta do mlx_loop:
 *   1. update_player() -> le as bandeiras, gira, anda (move.c)
 *   2. o raycasting pinta a imagem AQUI (a parte que falta)
 *   3. put_image -> joga o frame na tela
 */

#include "cub3d.h"

int	close_hook(void *param)
{
	return (cleanup((t_scene *)param, 0));
}

int	render_hook(void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	update_player(scene);
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win,
		scene->mlx.img.ptr, 0, 0);
	return (0);
}
