#ifndef CUB3D_H
# define CUB3D_H

typedef enum e_dir
{
	DIR_N,
	DIR_S,
	DIR_E,
	DIR_W,
} t_dir;

typedef struct s_rgb
{
	int r;
	int g;
	int b;
} t_rgb;

typedef struct s_config
{
	char *tex_n;
	char *tex_s;
	char *tex_w;
	char *tex_e;
	t_rgb floor;
	t_rgb ceiling;
	int f_set;
	int c_set;
} t_config;

typedef struct s_map
{
	char **grid;
	int height;
	int width;
	int player_x;
	int player_y;
	t_dir player_dir;
	int has_player;
} t_map;

typedef struct s_scene
{
	t_config config;
	t_map map;
} t_scene;

int parse_map(char **lines, int start, t_map *map);
void free_map(t_map *map);

int check_args(int ac, char **av);
int fail(char *msg);

int check_closed(t_map *map);
int check_textures(t_config *cfg);

int parse_config(char **lines, t_config *cfg);
void free_config(t_config *cfg);

char **read_file_lines(char *path);
void free_lines(char **lines);

#endif
