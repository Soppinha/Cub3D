/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:30:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"

# define WIN_W	1280
# define WIN_H	720
# define KEY_ESC	65307

typedef enum e_dir
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
}	t_dir;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_config
{
	char	*tex_n;
	char	*tex_s;
	char	*tex_w;
	char	*tex_e;
	t_rgb	floor;
	t_rgb	ceiling;
	int		f_set;
	int		c_set;
}	t_config;

typedef struct s_map
{
	char	**grid;
	int		height;
	int		width;
	int		player_x;
	int		player_y;
	t_dir	player_dir;
	int		has_player;
}	t_map;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
}	t_mlx;

typedef struct s_scene
{
	t_config	config;
	t_map		map;
	t_mlx		mlx;
}	t_scene;

typedef struct s_bfs
{
	char	*vis;
	int		*queue;
	int		head;
	int		tail;
	int		h;
	int		w;
}	t_bfs;

int		parse_map(char **lines, int start, t_map *map);
void	free_map(t_map *map);

int		check_args(int ac, char **av);
int		fail(char *msg);

int		check_closed(t_map *map);
int		check_textures(t_config *cfg);
char	padded_cell(t_map *map, int y, int x);
int		is_walkable(char c);

int		validate_charset(char *line);
int		find_player(char *line, int y, t_map *map);

int		parse_config(char **lines, t_config *cfg);
void	free_config(t_config *cfg);
int		is_config_line(char *line);
int		parse_config_line(char *line, t_config *cfg);
int		set_texture(char **slot, char *line, int id_len);
int		set_color(t_rgb *color, int *seen, char *line);

char	**read_file_lines(char *path);
void	free_lines(char **lines);

int		init_window(t_scene *scene);
int		cleanup(t_scene *scene, int status);
int		key_hook(int keycode, void *param);
int		close_hook(void *param);
int		render_hook(void *param);

#endif
