/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:04:56 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"

# define WIN_W	1280
# define WIN_H	720
# define KEY_ESC	65307

/* --- key inputs (keysyms X11, mesma familia do KEY_ESC) --- */
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

/*
 * Traduzimos o keycode da X11 pra um indice pequeno (0 a 5),
 * porque o keycode das SETAS (65361...) e maior que 256.
 * Assim keys[] so guarda as teclas que importam pro jogo.
 */
# define IDX_W		0
# define IDX_A		1
# define IDX_S		2
# define IDX_D		3
# define IDX_LEFT	4
# define IDX_RIGHT	5
# define KEY_COUNT	6

/* --- o passo do jogador: a "velocidade" da mecanica --- */
# define MOVE_SPEED	0.12	/* celulas por frame (frame = 1 volta do loop) */
# define ROT_SPEED	0.08	/* radios girados por frame */
# define MOUSE_SENS	0.002	/* bonus: mouse look */

/* --- o FOV e a constante do circo --- */
# define PLANE_LEN	0.66	/* FOV de ~66 graus: a "tela de lado" */
# define PI		3.14159265358979323846

# include <math.h>

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
	int		width;
	int		height;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_img	wall_tex[4];
}	t_mlx;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	wall_dist;
	t_img	*tex;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		tex_x;
	int		draw_start;
	int		draw_end;
	int		line_height;
}	t_ray;

/*
 * O JOGADOR VIVO: quem anda pelo mapa.
 * O t_map guarda o player em INTEIROS (a celula onde nasceu).
 * O t_player guarda a posicao REAL, em double, pra andar suave.
 */
typedef struct s_player
{
	double	x;
	double	y;
	double	angle;		/* pra onde a camera olha (em radios) */
	double	dir_x;		/* vetor direcao: o raycasting consome */
	double	dir_y;
	double	plane_x;	/* vetor camera (FOV): o raycasting consome */
	double	plane_y;
	int		keys[KEY_COUNT];
	int		mouse_dx;	/* delta X do mouse (porta pro bonus futuro) */
}	t_player;

typedef struct s_scene
{
	t_config	config;
	t_map		map;
	t_mlx		mlx;
	t_player	player;
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
int		key_press(int keycode, void *param);
int		key_release(int keycode, void *param);
int		close_hook(void *param);
int		render_hook(void *param);
int		load_textures(t_scene *scene);

void	render_frame(t_scene *scene);
void	init_ray(t_ray *ray, t_scene *scene, int x);
void	run_dda(t_ray *ray, t_map *map);
void	draw_column(t_scene *scene, t_ray *ray, int x);

void	put_pixel(t_img *img, int x, int y, int color);
int		tex_color(t_img *tex, int tx, int ty);
int		floor_color(t_scene *scene, int is_floor);
int		wall_pixel_color(t_ray *ray, int y);

/* --- mecanica (a parte nova): bandeiras + movimento --- */
void	set_key_flag(int keycode, int value, t_scene *scene);
void	init_player(t_scene *scene);
void	update_player(t_scene *scene);

#endif
