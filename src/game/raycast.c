/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 20:10:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:10:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cast_column(t_scene *scene, int x)
{
	t_ray	ray;

	init_ray(&ray, scene, x);
	run_dda(&ray, &scene->map);
	draw_column(scene, &ray, x);
}

void	render_frame(t_scene *scene)
{
	int	x;

	x = 0;
	while (x < WIN_W)
	{
		cast_column(scene, x);
		x++;
	}
}
