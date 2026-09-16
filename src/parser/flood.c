/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>

static int	bfs_init(t_bfs *b, int h, int w)
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

static void	bfs_push(t_bfs *b, t_map *map, int y, int x)
{
	char	c;
	int		pos;

	if (y < 0 || x < 0 || y >= b->h || x >= b->w)
		return ;
	pos = y * b->w + x;
	if (b->vis[pos])
		return ;
	c = padded_cell(map, y, x);
	if (!is_walkable(c))
		return ;
	b->vis[pos] = 1;
	b->queue[b->tail++] = pos;
}

static int	bfs_run(t_bfs *b, t_map *map)
{
	int		pos;
	char	c;

	while (b->head < b->tail)
	{
		pos = b->queue[b->head++];
		c = padded_cell(map, pos / b->w, pos % b->w);
		if (c != ' ')
			return (0);
		bfs_push(b, map, pos / b->w - 1, pos % b->w);
		bfs_push(b, map, pos / b->w + 1, pos % b->w);
		bfs_push(b, map, pos / b->w, pos % b->w - 1);
		bfs_push(b, map, pos / b->w, pos % b->w + 1);
	}
	return (1);
}

static void	bfs_free(t_bfs *b)
{
	free(b->vis);
	free(b->queue);
}

int	check_closed(t_map *map)
{
	t_bfs	b;
	int		ok;

	if (!bfs_init(&b, map->height + 2, map->width + 2))
		return (fail("malloc failed"));
	ok = bfs_run(&b, map);
	bfs_free(&b);
	if (!ok)
		return (fail("map is not closed"));
	return (1);
}
