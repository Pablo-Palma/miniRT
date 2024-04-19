/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersect2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:30:20 by math              #+#    #+#             */
/*   Updated: 2024/04/19 18:41:18 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_intersect_cy_caps(t_vec3 origin, t_vec3 dir, t_cyl cyl,
		double *t_cap)
{
	t_vec3	cap_normal;
	double	cap_t[2] = {INFINITY, INFINITY};
	int		hit = 0;
	int		i = 0;
	double	sign;

	cap_normal = cyl.dir;
	sign = 1.0;
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

static void	get_discriminant_cyl(t_cyl *cyl, t_ray *ray,
	t_vec3 diff, t_bhaskara *eq)
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

	double t_temp;
	t_temp = INFINITY;
	int	cap_hit = get_intersect_cy_caps(ray->origin, ray->direction, *cyl, &t_temp);
	if (cap_hit)
	{
		hit ++;
		if (t_temp < ray->t)
		{
			cyl->caps = cap_hit;
			ray->t = t_temp;
		}
	}
	if (hit)
		return (1);
	return (0);
}
