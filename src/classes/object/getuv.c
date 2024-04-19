/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getuv.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:18:45 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/19 10:23:57 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "miniRT.h"

void	get_uv_sp(double *u, double *v, t_vec3 p)
{
	double	phi;
	double	theta;

	phi = atan2(p.z, p.x);
	theta = asin(p.y);
	*u = 1 - (phi + M_PI) / (2 * M_PI);
	*v = (theta + M_PI / 2) / M_PI;
}

void	get_uv_cap(double *u, double *v, t_cyl cyl, t_vec3 point)
{
	t_vec3	local_point;

	local_point = vector_sub(point, cyl.center);
	*u = (local_point.x / cyl.radius + 1) / 2;
	*v = (local_point.y / cyl.radius + 1) / 2;
}

void	get_uv_cyl(double *u, double *v, t_cyl cyl, t_vec3 point)
{
	t_vec3	temp_vec;
	double	proj_length;
	double	height;

	temp_vec = vector_sub(point, cyl.center);
	proj_length = vector_dot_product(temp_vec, cyl.dir);
	temp_vec = vector_sub(temp_vec, vector_scale(cyl.dir, proj_length));
	*u = (atan2(temp_vec.y, temp_vec.x) + M_PI) / (2 * M_PI);
	*u = fmod(*u, 1.0);
	height = proj_length + (cyl.h / 2.0);
	*v = height / cyl.h;
	*v = fmod(*v, 1.0);
}
