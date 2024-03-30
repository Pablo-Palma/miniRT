/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:27:31 by math              #+#    #+#             */
/*   Updated: 2024/03/30 02:41:59 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static t_vec3	normal_pl(t_plane *plane, t_vec3 point)
{
	(void)point;
	return (plane->normal);
}

static t_vec3	normal_sp(t_sphere *sphere, t_vec3 point)
{
	return (normalize(vector_sub(point, sphere->center)));
}

static t_vec3	normal_cyl(t_cyl *cyl, t_vec3 point)
{
	t_vec3	normal;
	t_vec3	to_surface;
	t_vec3	closest_point;
	t_vec3	to_point;
	double	projection;

	to_surface = vector_sub(point, cyl->center);
	projection = vector_dot_product(to_surface, cyl->dir);
	closest_point = vector_add(cyl->center, vector_scale(cyl->dir, projection));
	to_point = vector_sub(point, closest_point);
	normal = vector_sub(to_point, vector_scale(cyl->dir,
				vector_dot_product(to_point, cyl->dir)));
	return (normal);
}

t_vec3	get_normal(t_obj *obj, t_vec3 point)
{
	if (is_child(obj, "pl"))
		return (normal_pl((t_plane *)obj->child, point));
	else if (is_child(obj, "sp"))
		return (normal_sp((t_sphere *)obj->child, point));
	else if (is_child(obj, "cy"))
		return (normal_cyl((t_cyl *)obj->child, point));
	else
		return (point);
}