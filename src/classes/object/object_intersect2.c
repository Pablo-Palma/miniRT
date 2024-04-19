/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersect2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:30:20 by math              #+#    #+#             */
/*   Updated: 2024/04/19 19:32:51 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	aux2(t_cyl *cyl, t_ray *ray, t_vec3 *cap_center, double d)
{
	t_vec3	p;
	double	distance;

	p = vector_add(ray->origin, vector_scale(ray->direction, d));
	distance = vector_length(vector_sub(p, *cap_center));
	if (distance <= cyl->radius + EPSILON)
	{
		return (1);
	}
	return (0);
}

static int	aux(t_cyl *cyl, t_ray *ray, double sign)
{
	t_vec3	cap_center;
	double	denominator;
	double	d;

	cap_center = vector_add(cyl->center, vector_scale(cyl->dir, sign * (cyl->h
					/ 2)));
	denominator = vector_dot_product(ray->direction, cyl->dir);
	if (fabs(denominator) > EPSILON)
	{
		d = vector_dot_product(vector_sub(cap_center, ray->origin), cyl->dir)
			/ denominator;
		if (d >= 0 && d < INFINITY)
		{
			if (d < ray->t && aux2(cyl, ray, &cap_center, d))
			{
				if (sign > 0)
					cyl->caps = 2;
				else
					cyl->caps = 1;
				ray->t = d;
			}
		}
	}
	return (0);
}

// static int	get_intersect_cy_caps(t_ray *ray, t_cyl *cyl)
// {
// 	int	hit;

// 	hit = 0;
// 	hit += aux(cyl, ray, 1.0);
// 	hit += aux(cyl, ray, -1.0);
// 	return (hit);
// }

static void	get_discriminant_cyl(t_cyl *cyl, t_ray *ray, t_vec3 diff,
		t_bhaskara *eq)
{
	t_vec3	dir_cross_cyl_dir;
	t_vec3	diff_cross_cyl_dir;

	dir_cross_cyl_dir = vector_cross(ray->direction, cyl->dir);
	diff_cross_cyl_dir = vector_cross(diff, cyl->dir);
	eq->a = vector_dot_product(dir_cross_cyl_dir, dir_cross_cyl_dir);
	eq->b = 2 * vector_dot_product(dir_cross_cyl_dir, diff_cross_cyl_dir);
	eq->c = vector_dot_product(diff_cross_cyl_dir, diff_cross_cyl_dir)
		- (cyl->radius * cyl->radius);
	eq->discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
}

static int	is_real_point(double *t, t_vec3 *cyl_origin, t_ray *ray, t_cyl *cyl)
{
	double	h;

	if (*t >= EPSILON)
	{
		h = vector_dot_product(vector_add(*cyl_origin,
					vector_scale(ray->direction, *t)), cyl->dir);
		if (fabs(h) <= cyl->h / 2 && *t < ray->t)
		{
			ray->t = *t;
			return (1);
		}
	}
	return (0);
}

int	intersect_cyl(t_cyl *cyl, t_ray *ray)
{
	int			hit;
	t_bhaskara	eq;
	t_vec3		cyl_origin;

	cyl->caps = 0;
	cyl_origin = vector_sub(ray->origin, cyl->center);
	get_discriminant_cyl(cyl, ray, cyl_origin, &eq);
	if (eq.discriminant < 0)
		return (0);
	get_bhaskara(&eq);
	hit = 0;
	hit += is_real_point(&eq.t0, &cyl_origin, ray, cyl);
	hit += is_real_point(&eq.t1, &cyl_origin, ray, cyl);
	hit += aux(cyl, ray, 1.0);
	hit += aux(cyl, ray, -1.0);
	if (hit)
		return (1);
	return (0);
}
