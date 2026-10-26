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

/*
 * O JOGADOR VIVO (a parte 2 da mecanica).
 *
 * init_player:     o jogador NASCE (do t_map inteiro pro double).
 * update_dir:      converte o angulo nos vetores (dir e plane).
 * update_player:    o loop chama 60x por segundo: le as bandeiras,
 *                  gira, anda, e nao deixa atravessar parede.
 *
 * Contrato com o raycasting: ele consome player->x, player->y,
 * dir_x, dir_y, plane_x, plane_y. Se esses seis numeros estao
 * certos, a imagem nasce certa.
 */

#include "cub3d.h"

/* Converte o angulo em vetores. Recalculado sempre que gira. */
static void	update_dir(t_scene *scene)
{
	t_player	*p;

	p = &scene->player;
	p->dir_x = cos(p->angle);
	p->dir_y = sin(p->angle);
	p->plane_x = -sin(p->angle) * PLANE_LEN;
	p->plane_y = cos(p->angle) * PLANE_LEN;
}

/* O chao do mapa: is_walkable() diz se o ponto e piso */
static int	can_stand(t_scene *scene, double x, double y)
{
	if (y < 0 || y >= scene->map.height
		|| x < 0 || x >= scene->map.width)
		return (0);
	return (is_walkable(scene->map.grid[(int)y][(int)x]));
}

/*
 * Andar sem atravessar parede: testa X e Y SEPARADO.
 * Se X livre, anda em X. Se Y livre, anda em Y.
 * Bater de frente: para. Bater de raspao: DESLIZA na parede.
 */
static void	try_move(t_scene *scene, double dx, double dy)
{
	t_player	*p;

	p = &scene->player;
	if (can_stand(scene, p->x + dx, p->y))
		p->x += dx;
	if (can_stand(scene, p->x, p->y + dy))
		p->y += dy;
}

/* O jogador nasce no CENTRO da celula onde o mapa o achou. */
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
	update_dir(scene);
}

/*
 * Chamado pelo render_hook, uma vez por frame. Le as bandeiras
 * do keys.c e transforma em giro + passo. W e S andam no vetor
 * direcao; A e D fazem STRAFE: andar de lado, no vetor
 * PERPENDICULAR a direcao (troca dir por -dir rotacionado).
 */
void	update_player(t_scene *scene)
{
	t_player	*p;

	p = &scene->player;
	if (p->keys[IDX_LEFT])
		p->angle -= ROT_SPEED;
	if (p->keys[IDX_RIGHT])
		p->angle += ROT_SPEED;
	if (p->keys[IDX_W])
		try_move(scene, p->dir_x * MOVE_SPEED, p->dir_y * MOVE_SPEED);
	if (p->keys[IDX_S])
		try_move(scene, -p->dir_x * MOVE_SPEED, -p->dir_y * MOVE_SPEED);
	if (p->keys[IDX_A])
		try_move(scene, p->dir_y * MOVE_SPEED, -p->dir_x * MOVE_SPEED);
	if (p->keys[IDX_D])
		try_move(scene, -p->dir_y * MOVE_SPEED, p->dir_x * MOVE_SPEED);
	if (p->mouse_dx)
	{
		p->angle += p->mouse_dx * MOUSE_SENS;
		p->mouse_dx = 0;
	}
	update_dir(scene);
}
