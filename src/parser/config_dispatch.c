/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_dispatch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 19:45:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_config_id(char *line, char *id)
{
	int	i;

	i = 0;
	while (id[i])
	{
		if (line[i] != id[i])
			return (0);
		i++;
	}
	return (line[i] == ' ' || line[i] == '\t');
}

int	is_config_line(char *line)
{
	return (is_config_id(line, "NO") || is_config_id(line, "SO")
		|| is_config_id(line, "WE") || is_config_id(line, "EA")
		|| is_config_id(line, "F") || is_config_id(line, "C"));
}

int	parse_config_line(char *line, t_config *cfg)
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
