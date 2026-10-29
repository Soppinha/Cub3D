/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 12:00:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/10/29 12:00:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	can_stand(t_scene *scene, double x, double y)
{
	if (y < 0 || y >= scene->map.height || x < 0)
		return (0);
	return (x < (double)ft_strlen(scene->map.grid[(int)y]));
}
