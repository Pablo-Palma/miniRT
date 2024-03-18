/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:26:07 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/18 20:45:59 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cap_uv(t_vec3 hit_point, t_cyl cyl, double *u, double *v)
{
	t_vec3	point_vector = vector_sub(hit_point, cyl.center);
	double	angle = atan2(point_vector.z, point_vector.x);
	double	radius = sqrt(point_vector.x * point_vector.x + point_vector.z * point_vector.z);
	*u = (angle + M_PI) / (2 * M_PI);
	*v = radius / cyl.radius;
	*u = fmod(*u, 1.0);
	*v = fmod(*v, 1.0);
}
