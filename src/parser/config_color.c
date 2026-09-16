/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 19:45:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:45:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_component(char *s, int *i, int *out)
{
	int	n;
	int	digits;

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

static int	parse_rgb(char *s, t_rgb *color)
{
	int	i;
	int	r;
	int	g;
	int	b;

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

int	set_color(t_rgb *color, int *seen, char *line)
{
	if (*seen)
		return (fail("duplicate color identifier"));
	*seen = 1;
	return (parse_rgb(line + 1, color));
}
