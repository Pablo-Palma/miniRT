/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:32:16 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/17 20:21:23 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int check_pl(t_plane *plane)
{
	if (!plane)
		return (EXIT_FAILURE);
	if (check_direction(plane->normal) || check_color(plane->color))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int check_sp(t_sphere *sphere)
{
	if (!sphere)
		return (EXIT_FAILURE);
	if (check_color(sphere->color0))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int check_cyl(t_cyl *cylinder)
{
	if (!cylinder)
		return (EXIT_FAILURE);
	if (check_direction(cylinder->dir) || check_color(cylinder->color))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int check_light(t_light *light)
{
	if (!light)
		return (EXIT_FAILURE);
	if (check_light_brightness(light->brigthness) || check_color(light->color))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int check_a_light(t_ambient_light *a_light)
{
	if (!a_light)
		return (EXIT_FAILURE);
	if (check_light_brightness(a_light->intensity))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int check_cam(t_cam *cam)
{
	if (!cam)
		return (EXIT_FAILURE);
	if (check_direction(cam->orientation) || check_fov(cam->fov))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int check(t_obj *obj)
{
	int	ret;

	ret = EXIT_FAILURE;
    if (is_child(obj, "pl"))
        ret = check_pl((t_plane *)(obj->child));
    else if (is_child(obj, "sp"))
        ret = check_sp((t_sphere *)(obj->child));
	else if (is_child(obj, "cy"))
        ret = check_cyl((t_cyl *)(obj->child));
	else if (is_child(obj, "L"))
        ret = check_light((t_light *)(obj->child));
	else if (is_child(obj, "A"))
        ret = check_a_light((t_ambient_light *)(obj->child));
	else if (is_child(obj, "C"))
        ret = check_cam((t_cam *)(obj->child));
	if (ret)
	{
		printf("MiniRt: Invalid Object\n");
	}
	return (ret);
}
