/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:32:16 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/17 18:29:56 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int check_pl(t_plane *plane)
{
	if (!plane)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int check_sp(t_sphere *sphere)
{
	if (!sphere)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int check_cyl(t_cyl *cylinder)
{
	if (!cylinder)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int check_light(t_light *light)
{
	if (!light)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int check_a_light(t_ambient_light *a_light)
{
	if (!a_light)
		return (EXIT_FAILURE);
	printf("%p\n", a_light);
	return (EXIT_SUCCESS);
}

static int check_cam(t_cam *cam)
{
	if (!cam)
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
