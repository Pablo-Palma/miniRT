/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersect2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:30:20 by math              #+#    #+#             */
/*   Updated: 2024/04/19 10:33:23 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_intersect_cy_caps(t_vec3 origin, t_vec3 dir, t_cyl cyl,
	double *t_cap)
{
	t_vec3	cap_normal = cyl.dir;
	double	cap_t[2] = {INFINITY, INFINITY};
	int		hit = 0;
	int		i = 0;
	double	sign = 1.0;

	while (i < 2)
	{
		t_vec3	cap_center = vector_add(cyl.center, vector_scale(cap_normal, sign * (cyl.h / 2)));
		double denominator = vector_dot_product(dir, cap_normal);
		if (fabs(denominator) > EPSILON)
		{
			double d = vector_dot_product(vector_sub(cap_center, origin), cap_normal) / denominator;
			if (d >= 0 && d < *t_cap)
			{
				t_vec3	p = vector_add(origin, vector_scale(dir, d));
				double	distance = vector_length(vector_sub(p, cap_center));
				if (distance <= cyl.radius + EPSILON)
				{
					cap_t[i] = d;
					hit = 1;
				}
			}
		}
		i++;
		sign = -sign;
	}

	if (hit)
	{
		double	closest_t = cap_t[0];
		if (cap_t[1] < cap_t[0])
			closest_t = cap_t[1];
		*t_cap = closest_t;
		if (cap_t[1] < cap_t[0])
			return (1);
		return (2);
	}
	return(0);
}

int	intersect_cyl(t_cyl *cyl, t_ray *ray)
{
	cyl->caps = 0;
	t_vec3 diff = vector_sub(ray->origin, cyl->center);
	t_vec3 dir_cross_cyl_dir = vector_cross(ray->direction, cyl->dir);
	t_vec3 diff_cross_cyl_dir = vector_cross(diff, cyl->dir);
	
	double a = vector_dot_product(dir_cross_cyl_dir, dir_cross_cyl_dir);
	double b = 2 * vector_dot_product(dir_cross_cyl_dir, diff_cross_cyl_dir);
	double c = vector_dot_product(diff_cross_cyl_dir, diff_cross_cyl_dir) - (cyl->radius * cyl->radius);
	
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	    return 0;
	
	double sqrt_discriminant = sqrt(discriminant);
	double t0 = (-b - sqrt_discriminant) / (2 * a);
	double t1 = (-b + sqrt_discriminant) / (2 * a);
	
	double t_body = INFINITY;
	int body_hit = 0;
	if (t0 >= EPSILON)
	{
	    double h0 = vector_dot_product(vector_add(diff, vector_scale(ray->direction, t0)), cyl->dir);
	    if (fabs(h0) <= cyl->h / 2)
		{
	        t_body = t0;
	        body_hit = 1;
	    }
	}
	
	if (t1 >= EPSILON && t1 < t_body)
	{
	    double h1 = vector_dot_product(vector_add(diff, vector_scale(ray->direction, t1)), cyl->dir);
	    if (fabs(h1) <= cyl->h / 2)
		{
			t_body = t1;
			body_hit = 1;
	    }
	}
	
	double t_cap = INFINITY;
	int cap_hit = get_intersect_cy_caps(ray->origin, ray->direction, *cyl, &t_cap);
	
	if (cap_hit && (t_cap < t_body || !body_hit))
	{
		if (ray->t < t_cap)
			return (0);
		ray->t = t_cap;
		cyl->caps = cap_hit;
		return (1);
	}
	else if (body_hit)
	{
		if (ray->t < body_hit)
			return (0);
		ray->t = t_body;
		return 1;
	}
	return 0;
}
