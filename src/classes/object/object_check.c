/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:32:16 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/18 22:22:55 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	check_pl(t_plane *plane)
{
	if (!plane)
		return (EXIT_FAILURE);
	if (check_direction(plane->normal) || check_color(plane->color))
		return (EXIT_FAILURE);
	if (check_unitary_vec(&plane->normal))
		return (2);
	return (EXIT_SUCCESS);
}

int	check_sp(t_sphere *sphere)
{
	if (!sphere)
		return (EXIT_FAILURE);
	if (check_color(sphere->color))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_cyl(t_cyl *cylinder)
{
	if (!cylinder)
		return (EXIT_FAILURE);
	if (check_direction(cylinder->dir) || check_color(cylinder->color))
		return (EXIT_FAILURE);
	if (check_unitary_vec(&cylinder->dir))
		return (2);
	return (EXIT_SUCCESS);
}

int	check_light(t_light *light)
{
	if (!light)
		return (EXIT_FAILURE);
	if (check_light_brightness(light->brigthness) || check_color(light->color))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_a_light(t_ambient_light *a_light)
{
	if (!a_light)
		return (EXIT_FAILURE);
	if (check_light_brightness(a_light->intensity)
		|| check_color(a_light->color))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
