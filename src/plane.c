/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:03:29 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/06 14:10:07 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	intersect_ray_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane plane, double *t)
{
	double	denom;

	denom = vector_dot_product(ray_dir, plane.normal);
	if (fabs(denom) > 1e-6)
	{
		t_vec3	origin_plane = vector_sub(plane.point, ray_origin);
		*t = vector_dot_product(origin_palne, plane.normal) / denom;
		return(*t >= 0)
	}
	return (0);
}
