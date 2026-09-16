/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 20:10:00 by svaladar          #+#    #+#             */
/*   Updated: 2026/09/16 20:10:00 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

double	get_delta_time(t_scene *scene)
{
	struct timeval	tv;
	double			now;
	double			dt;

	gettimeofday(&tv, NULL);
	now = tv.tv_sec + tv.tv_usec / 1000000.0;
	dt = now - scene->last_time;
	scene->last_time = now;
	if (dt > 0.1)
		dt = 0.1;
	return (dt);
}
