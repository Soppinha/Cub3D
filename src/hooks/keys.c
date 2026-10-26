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

/*
 * AS BANDEIRAS (a parte 1 da mecanica).
 *
 * O mlx_key_hook antigo era um SININHO: toca uma vez quando a tecla
 * desce, e pronto. Pra andar segurando a tecla, a gente troca o
 * sininho por BANDEIRAS:
 *
 *   key_press  -> bandeira SOBE   (keys[IDX_W] = 1)
 *   key_release-> bandeira DESCE  (keys[IDX_W] = 0)
 *   o render_hook (60x por segundo) olha as bandeiras e anda.
 *
 * Nao sao "muitos eventos": sao DOIS eventos por tecla (apertou,
 * soltou) e um ESTADO que fica de pe entre eles. O movimento
 * continuo nasce do loop consumindo a bandeira, nao do teclado
 * gritando.
 */

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

/* Sobe (value = 1) ou desce (value = 0) a bandeira de uma tecla. */
void	set_key_flag(int keycode, int value, t_scene *scene)
{
	int	idx;

	idx = key_index(keycode);
	if (idx >= 0)
		scene->player.keys[idx] = value;
}

/*
 * BANDEIRA SOBE: a X11 avisa UMA vez que a tecla desceu.
 * (Aqui tambem mora o ESC, que e pressao unica mesmo.)
 */
int	key_press(int keycode, void *param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	if (keycode == KEY_ESC)
		cleanup(scene, 0);
	set_key_flag(keycode, 1, scene);
	return (0);
}

/*
 * BANDEIRA DESCE: a X11 avisa que a tecla foi soltada.
 * Sem isso, o jogador andaria pra sempre (tecla fantasma).
 */
int	key_release(int keycode, void *param)
{
	set_key_flag(keycode, 0, (t_scene *)param);
	return (0);
}
