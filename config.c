#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

static int check_texture(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}

int check_textures(t_config *cfg)
{
	if (!check_texture(cfg->tex_n))
		return (fail("missing texture: NO"));
	if (!check_texture(cfg->tex_s))
		return (fail("missing texture: SO"));
	if (!check_texture(cfg->tex_w))
		return (fail("missing texture: WE"));
	if (!check_texture(cfg->tex_e))
		return (fail("missing texture: EA"));
	return (1);
}
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

static char *skip_spaces(char *s)
{
	while (*s == ' ' || *s == '\t')
		s++;
	return (s);
}

static int is_config_id(char *line, char *id)
{
	int i;

	i = 0;
	while (id[i])
	{
		if (line[i] != id[i])
			return (0);
		i++;
	}
	return (line[i] == ' ' || line[i] == '\t');
}

static char *trim_dup(char *s)
{
	char *start;
	int len;

	start = skip_spaces(s);
	len = ft_strlen(start);
	while (len > 0 && (start[len - 1] == ' ' || start[len - 1] == '\t'))
		len--;
	if (len==0)
		return (NULL);
	return (ft_substr(start, 0, len));
}

static int set_texture(char **slot, char *line, int id_len)
{
	char *path;

	path = trim_dup(line + id_len);
	if (!path)
		return (fail("empty texture path"));
	if (*slot)
	{
		free(path);
		return (fail("duplicate texture identifier"));
	}
	*slot = path;
	return (1);
}

static int read_component(char *s, int *i, int *out)
{
	int n;
	int digits;

	n = 0;
	digits = 0;
	while (s[*i] == ' ')
		(*i)++;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		n = n * 10 + (s[*i] - '0');
		(*i)++;
		digits++;
	}
	if (digits == 0 || n > 255)
		return (0);
	*out = n;
	return (1);
}

static int parse_rgb(char *s, t_rgb *color)
{
	int i;
	int r;
	int g;
	int b;

	i = 0;
	if (!read_component(s, &i, &r) || s[i] != ',')
		return (fail("invalid color"));
	i++;
	if (!read_component(s, &i, &g) || s[i] != ',')
		return (fail("invalid color"));
	i++;
	if (!read_component(s, &i, &b))
		return (fail("invalid color"));
	while (s[i] == ' ')
		i++;
	if (s[i] != '\0')
		return (fail("invalid color"));
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}

static int set_color(t_rgb *color, int *seen, char *line)
{
	if (*seen)
		return (fail("duplicate color identifier"));
	*seen = 1;
	return (parse_rgb(line + 1 , color));
}

static int is_config_line(char *line)
{
	return (is_config_id(line, "NO") || is_config_id(line, "SO")
			|| is_config_id(line, "WE") || is_config_id(line, "EA")
			|| is_config_id(line, "F") || is_config_id(line,"C"));
}

static int parse_config_line(char *line, t_config *cfg)
{
	if (is_config_id(line, "NO"))
		return (set_texture(&cfg->tex_n, line, 2));
	if (is_config_id(line, "SO"))
		return (set_texture(&cfg->tex_s, line, 2));
	if (is_config_id(line, "WE"))
		return (set_texture(&cfg->tex_w, line, 2));
	if (is_config_id(line, "EA"))
		return (set_texture(&cfg->tex_e, line, 2));
	if (is_config_id(line, "F"))
		return (set_color(&cfg->floor, &cfg->f_set, line));
	if (is_config_id(line, "C"))
		return (set_color(&cfg->ceiling, &cfg->c_set, line));
	return (0);
}

int parse_config(char **lines, t_config *cfg)
{
	int i;

	i = 0;
	while (lines[i] && is_blank(lines[i]))
		i++;
	while (lines[i] && !is_blank(lines[i]) && is_config_line(lines[i]))
	{
		if (!parse_config_line(lines[i], cfg))
			return(-1);
		i++;
	}
	if (!cfg->tex_n || !cfg->tex_s || !cfg->tex_w || !cfg->tex_e
			|| !cfg->f_set || !cfg->c_set)
	{
		fail("missing configuration element");
		return (-1);
	}
	return (i);
}

void free_config(t_config *cfg)
{
	if (cfg->tex_n)
		free(cfg->tex_n);
	if (cfg->tex_s)
		free(cfg->tex_s);
	if (cfg->tex_w)
		free(cfg->tex_w);
	if (cfg->tex_e)
		free(cfg->tex_e);
}
