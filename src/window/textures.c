/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 20:10:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:10:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	load_texture(t_scene *scene, char *path, t_img *img)
{
	img->ptr = mlx_xpm_file_to_image(scene->mlx.mlx, path,
			&img->width, &img->height);
	if (!img->ptr)
		return (fail("failed to load texture"));
	img->addr = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_len, &img->endian);
	return (1);
}

int	load_textures(t_scene *scene)
{
	if (!load_texture(scene, scene->config.tex_n, &scene->mlx.wall_tex[DIR_N]))
		return (0);
	if (!load_texture(scene, scene->config.tex_s, &scene->mlx.wall_tex[DIR_S]))
		return (0);
	if (!load_texture(scene, scene->config.tex_e, &scene->mlx.wall_tex[DIR_E]))
		return (0);
	if (!load_texture(scene, scene->config.tex_w, &scene->mlx.wall_tex[DIR_W]))
		return (0);
	return (1);
}
