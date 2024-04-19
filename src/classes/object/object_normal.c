/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:27:31 by math              #+#    #+#             */
/*   Updated: 2024/04/19 12:05:02 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	normal_pl(t_plane *plane, t_vec3 point)
{
	(void)point;
	return (plane->normal);
}

t_vec3	normal_sp(t_sphere *sphere, t_vec3 point)
{
	return (normalize(vector_sub(point, sphere->center)));
}

t_vec3	normal_cyl(t_cyl *cyl, t_vec3 point)
{
	t_vec3	center_to_hit;
	double	proj_length;
	t_vec3	proj_point;
	t_vec3	normal;

	if (cyl->caps == 2)
		return (normalize(cyl->dir));
	else if (cyl->caps == 1)
		return (normalize(vector_negate(cyl->dir)));
	center_to_hit = vector_sub(point, cyl->center);
	proj_length = vector_dot_product(center_to_hit, cyl->dir);
	proj_point = vector_add(cyl->center, vector_scale(cyl->dir, proj_length));
	normal = vector_sub(point, proj_point);
	return (normalize(normal));
}
