/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:30:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	parse_scene(char **lines, t_scene *scene)
{
	int	map_start;

	map_start = parse_config(lines, &scene->config);
	if (map_start < 0 || !parse_map(lines, map_start, &scene->map)
		|| !check_closed(&scene->map) || !check_textures(&scene->config))
	{
		free_config(&scene->config);
		free_map(&scene->map);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	char	**lines;
	t_scene	scene;

	if (!check_args(ac, av))
		return (1);
	lines = read_file_lines(av[1]);
	if (!lines)
		return (1);
	ft_bzero(&scene, sizeof(t_scene));
	if (!parse_scene(lines, &scene))
	{
		free_lines(lines);
		return (1);
	}
	free_lines(lines);
	init_player(&scene);
	if (!init_window(&scene))
		return (cleanup(&scene, 1));
	mlx_loop(scene.mlx.mlx);
	return (0);
}
