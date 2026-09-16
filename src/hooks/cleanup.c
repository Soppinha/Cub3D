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

int	cleanup(t_scene *scene, int status)
{
	if (scene->mlx.img.ptr)
		mlx_destroy_image(scene->mlx.mlx, scene->mlx.img.ptr);
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
