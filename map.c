#include "cub3d.h"
#include "libft.h"

static int is_blank(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

static int is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
			|| c == 'E' || c == 'W' || c == ' ');
}

static int is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static t_dir dir_from_char(char c)
{
	if (c == 'N')
		return (DIR_N);
	if (c == 'S')
		return (DIR_S);
	if (c == 'E')
		return (DIR_E);
	return (DIR_W); //não precisa de if porque é a única opção possível
}

static int validate_charset(char *line)
{
	int x;

	x = 0;
	while (line[x])
	{
		if (!is_map_char(line[x]))
			return (fail("invalid character in map"));
		x++;
	}
	return (1);
}

static int find_player(char *line, int y, t_map *map)
{
	int x;

	x = 0;
	while (line[x])
	{
		if (is_player_char(line[x]))
		{
			if (map->has_player)
				return (fail("multi players in map"));
			map->has_player = 1;
			map->player_x = x;
			map->player_y = y;
			map->player_dir = dir_from_char(line[x]);
		}
		x++;
	}
	return(1);
}

static int fill_grid(t_map *map, char **lines, int start, int height)
{
	int y;
	int width;

	y = 0;
	width = 0;
	while (y < height)
	{
		map->grid[y] = ft_strdup(lines[start + y]);
		if (!map->grid[y])
			return (fail("malloc failed"));
		if (!validate_charset(map->grid[y]) || !find_player(map->grid[y], y, map))
			return (0);
		if ((int)ft_strlen(map->grid[y]) > width)
			width = (int)ft_strlen(map->grid[y]);
		y++;
	}
	map->width = width;
	return (1);
}

int parse_map(char **lines, int start, t_map *map)
{
	int i;
	int height;

	i = start;
	while (lines[i] && is_blank(lines[i]))
		i++;
	height = 0;
	while (lines[i + height] && !is_blank(lines[i + height]))
		height++;
	if (height == 0)
		return (fail("no map found"));
	map->grid = ft_calloc(height + 1, sizeof(char *));
	if (!map->grid)
		return (fail("no map found"));
	map->height = height;
	map->grid[height] = NULL;
	if (!fill_grid (map, lines, i, height))
		return (0);
	i += height;
	while (lines[i] && is_blank(lines[i]))
		i++;
	if (lines[i])
		return (fail("content after map"));
	if (!map->has_player)
		return (fail("no player in map"));
	return (1);
}

void free_map(t_map *map)
{
	int y;

	if (!map->grid)
		return ;
	y = 0;
	while (map->grid[y])
	{
		free(map->grid[y]);
		y++;
	}
	free(map->grid);
}
