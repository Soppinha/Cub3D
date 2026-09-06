#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

typedef struct s_bfs
{
	char *vis;
	int *queue;
	int head;
	int tail;
	int h;
	int w;
} t_bfs; //acho que talvez tenha que mover para .h devido norminette

static char padded_cell(t_map *map, int y, int x, int h, int w)
{
	if (y <= 0 || x <= 0 || y >= h -1 || x >= w - 1)
		return (' ');
	if (x - 1 >= (int)ft_strlen(map->grid[y - 1]))
		return (' ');
	return (map->grid[y - 1][x - 1]);
}

static int is_walkable(char c)
{
	return (c == ' ' || c == '0' || c == 'N' || c == 'S'
			|| c == 'E' || c == 'W');
}

static int bfs_init(t_bfs *b, int h, int w)
{
	b->h = h;
	b->w = w;
	b->head = 0;
	b->tail = 1;
	b->vis = ft_calloc(h * w, sizeof(char));
	b->queue = malloc(sizeof(int) * h * w);
	if (!b->vis || !b->queue)
	{
		free(b->vis);
		free(b->queue);
		return (0);
	}
	b->vis[0] = 1;
	b->queue[0] = 0;
	return (1);
}

static void bfs_push(t_bfs *b, t_map *map, int y, int x)
{
	char c;
	int pos;

	if (y < 0 || x < 0 || y >= b->h || x >= b->w)
		return ;
	pos = y * b->w + x;
	if (b->vis[pos])
		return ;
	c = padded_cell(map, y, x, b->h, b->w);
	if (!is_walkable(c))
		return ;
	b->vis[pos] = 1;
	b->queue[b->tail++] = pos;
}

static int bfs_run(t_bfs *b, t_map *map)
{
	int pos;
	char c;

	while (b->head < b->tail)
	{
		pos = b->queue[b->head++];
		c = padded_cell(map, pos / b->w, pos % b->w, b->h, b->w);
		if (c != ' ')
			return (0);
		bfs_push(b, map, pos / b->w - 1, pos % b->w);
		bfs_push(b, map, pos / b->w + 1, pos % b->w);
		bfs_push(b, map, pos / b->w, pos % b->w - 1);
		bfs_push(b, map, pos / b->w, pos % b->w + 1);
	}
	return (1);
}

static void bfs_free(t_bfs *b)
{
	free(b->vis);
	free(b->queue);
}

int check_closed(t_map *map)
{
	t_bfs b;
	int ok;

	if (!bfs_init(&b, map->height + 2, map->width + 2))
		return (fail("malloc failed"));
	ok = bfs_run(&b, map);
	bfs_free(&b);
	if (!ok)
		return (fail("map is not closed"));
	return (1);
}
