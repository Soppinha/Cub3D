#include "cub3d.h"
#include "libft.h"

static void print_heartbeat(t_scene *scene)
{
	int y;

	y = 0;
	while (scene->map.grid[y])
	{
		ft_putstr_fd(scene->map.grid[y], 1);
		ft_putstr_fd("\n", 1);
		y++;
	}
	ft_printf("player at (%d, %d) facing %d | grid %dx%d\n",
		scene->map.player_x, scene->map.player_y, scene->map.player_dir, scene->map.width, scene->map.height);
}	

int main(int ac, char **av)
{
	char **lines;
	t_scene scene;
	int map_start;

	if (!check_args(ac, av))
		return (1);
	lines = read_file_lines(av[1]);
	if (!lines)
		return (1);
	ft_bzero(&scene, sizeof(t_scene));
	map_start = parse_config(lines, &scene.config);
	if (map_start < 0 || !parse_map(lines, map_start, &scene.map) 
			|| !check_closed(&scene.map) || !check_textures(&scene.config))
	{
		free_config(&scene.config);
		free_map(&scene.map);
		free_lines(lines);
		return (1);
	}
	print_heartbeat(&scene);
	free_config(&scene.config);
	free_map(&scene.map);
	free_lines(lines);
	return (0);
}
