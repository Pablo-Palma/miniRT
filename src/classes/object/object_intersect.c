/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:28:25 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/19 11:56:50 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	intersect_pl(t_plane plane, t_ray *ray)
{
	double	denom;
	double	temp_t;
	t_vec3	origin_plane;

	denom = vector_dot_product(ray->direction, plane.normal);
	if (fabs(denom) > 1e-6)
	{
		origin_plane = vector_sub(plane.point, ray->origin);
		temp_t = vector_dot_product(origin_plane, plane.normal) / denom;
		if (temp_t >= 0 && temp_t < ray->t)
		{
			ray->t = temp_t;
			return (1);
		}
	}
	return (0);
}

int	intersect_sp(t_sphere sphere, t_ray *ray)
{
	t_vec3		oc;
	t_bhaskara	eq;

	oc = vector_sub(ray->origin, sphere.center);
	eq.a = vector_dot_product(ray->direction, ray->direction);
	eq.b = 2.0 * vector_dot_product(oc, ray->direction);
	eq.c = vector_dot_product(oc, oc) - sphere.radius * sphere.radius;
	eq.discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
	if (eq.discriminant < 0)
		return (0);
	get_bhaskara(&eq);
	if (eq.t0 > 0.0f && eq.t0 < ray->t)
		ray->t = eq.t0;
	else if (eq.t1 > 0.0f && eq.t1 < ray->t)
		ray->t = eq.t1;
	else
		return (0);
	return (1);
}

int	intersect_light(t_light light, t_ray *ray)
{
	t_sphere	light_space;

	light_space.center = light.pos;
	light_space.radius = 0.001;
	return (intersect_sp(light_space, ray));
}

int	intersect_circle(t_circle circle, t_ray *ray)
{
	t_plane		circle_plane;
	t_sphere	circle_sphere;
	double		ray_t;
	double		plane_t;

	ray_t = ray->t;
	circle_plane.point = circle.center;
	circle_plane.normal = circle.normal;
	if (!intersect_pl(circle_plane, ray))
		return (0);
	plane_t = ray->t;
	circle_sphere.center = circle.center;
	circle_sphere.radius = circle.radius;
	if (!intersect_sp(circle_sphere, ray))
	{
		ray->t = ray_t;
		return (0);
	}
	ray->t = plane_t;
	return (1);
}
