/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 20:10:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:10:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

int	tex_color(t_img *tex, int tx, int ty)
{
	char	*pixel;

	pixel = tex->addr + (ty * tex->line_len + tx * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}

int	floor_color(t_scene *scene, int is_floor)
{
	t_rgb	c;

	if (is_floor)
		c = scene->config.floor;
	else
		c = scene->config.ceiling;
	return ((c.r << 16) | (c.g << 8) | c.b);
}

int	wall_pixel_color(t_ray *ray, int y)
{
	double	step;
	int		tex_y;

	step = (double)ray->tex->height / ray->line_height;
	tex_y = (int)((y - WIN_H / 2 + ray->line_height / 2) * step);
	if (tex_y >= ray->tex->height)
		tex_y = ray->tex->height - 1;
	if (tex_y < 0)
		tex_y = 0;
	return (tex_color(ray->tex, ray->tex_x, tex_y));
}
