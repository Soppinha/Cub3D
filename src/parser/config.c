/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_blank(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\t')
			return (0);
		line++;
	}
	return (1);
}

int	parse_config(char **lines, t_config *cfg)
{
	int	i;

	i = 0;
	while (lines[i] && is_blank(lines[i]))
		i++;
	while (lines[i] && !is_blank(lines[i]) && is_config_line(lines[i]))
	{
		if (!parse_config_line(lines[i], cfg))
			return (-1);
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

void	free_config(t_config *cfg)
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
