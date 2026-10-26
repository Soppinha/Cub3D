/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:55:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:21:02 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_textures(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (scene->mlx.wall_tex[i].ptr)
			mlx_destroy_image(scene->mlx.mlx, scene->mlx.wall_tex[i].ptr);
		i++;
	}
}

int	cleanup(t_scene *scene, int status)
{
	if (scene->mlx.img.ptr)
		mlx_destroy_image(scene->mlx.mlx, scene->mlx.img.ptr);
	free_textures(scene);
	if (scene->mlx.win)
		mlx_destroy_window(scene->mlx.mlx, scene->mlx.win);
	if (scene->mlx.mlx)
	{
		mlx_destroy_display(scene->mlx.mlx);
		free(scene->mlx.mlx);
	}
	free_map(&scene->map);
	free_config(&scene->config);
	exit(status);
}
