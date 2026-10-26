/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 20:10:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:10:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static void	pick_wall_texture(t_scene *scene, t_ray *ray)
{
	if (ray->side == 1 && ray->step_y > 0)
		ray->tex = &scene->mlx.wall_tex[DIR_S];
	else if (ray->side == 1)
		ray->tex = &scene->mlx.wall_tex[DIR_N];
	else if (ray->step_x > 0)
		ray->tex = &scene->mlx.wall_tex[DIR_E];
	else
		ray->tex = &scene->mlx.wall_tex[DIR_W];
}

static void	compute_tex_x(t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = ray->pos_y + ray->wall_dist * ray->dir_y;
	else
		wall_x = ray->pos_x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * ray->tex->width);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		ray->tex_x = ray->tex->width - ray->tex_x - 1;
}

static void	compute_extent(t_ray *ray)
{
	if (ray->wall_dist < 0.0001)
		ray->wall_dist = 0.0001;
	ray->line_height = (int)(WIN_H / ray->wall_dist);
	if (ray->line_height < 1)
		ray->line_height = 1;
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

void	draw_column(t_scene *scene, t_ray *ray, int x)
{
	int	y;
	int	color;

	pick_wall_texture(scene, ray);
	compute_tex_x(ray);
	compute_extent(ray);
	y = 0;
	while (y < WIN_H)
	{
		if (y < ray->draw_start)
			color = floor_color(scene, 0);
		else if (y > ray->draw_end)
			color = floor_color(scene, 1);
		else
			color = wall_pixel_color(ray, y);
		put_pixel(&scene->mlx.img, x, y, color);
		y++;
	}
}
