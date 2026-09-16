/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 18:54:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 19:40:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

static int	has_cub_extension(char *name)
{
	int	len;

	len = 0;
	while (name[len])
		len++;
	if (len < 4)
		return (0);
	return (name[len - 4] == '.' && name[len - 3] == 'c'
		&& name[len - 2] == 'u' && name[len - 1] == 'b');
}

int	check_args(int ac, char **av)
{
	if (ac != 2)
	{
		write(1, "Usage: ./cub3d <map.cub>\n", 25);
		return (0);
	}
	if (!has_cub_extension(av[1]))
		return (fail("invalid map extension (.cub expected)"));
	return (1);
}
