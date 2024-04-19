/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersect2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:30:20 by math              #+#    #+#             */
/*   Updated: 2024/04/19 01:28:21 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	get_intersect_cy_caps(t_vec3 origin, t_vec3 dir, t_cyl cyl, double *t_cap)
{
	t_vec3	cap_normal = cyl.dir;
	double	cap_t[2] = {INFINITY, INFINITY};
	int		hit = 0;
	int		i = 0;
	double	sign = 1.0;

	while(i < 2)
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

static void get_bhaskara(t_bhaskara *eq)
{
	eq->sqrt_discriminant = sqrt(eq->discriminant);
	eq->t0 = (-eq->b - eq->sqrt_discriminant) / (2 * eq->a);
	eq->t1 = (-eq->b + eq->sqrt_discriminant) / (2 * eq->a);
}

static void	get_discriminant_cyl(t_cyl *cyl, t_ray *ray, t_vec3 diff, t_bhaskara *eq)
{
	t_vec3 dir_cross_cyl_dir;
	t_vec3 diff_cross_cyl_dir;
	
	dir_cross_cyl_dir = vector_cross(ray->direction, cyl->dir);
	diff_cross_cyl_dir= vector_cross(diff, cyl->dir);
	eq->a = vector_dot_product(dir_cross_cyl_dir, dir_cross_cyl_dir);
	eq->b = 2 * vector_dot_product(dir_cross_cyl_dir, diff_cross_cyl_dir);
	eq->c = vector_dot_product(diff_cross_cyl_dir, diff_cross_cyl_dir) - (cyl->radius * cyl->radius);
	eq->discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
}

int	intersect_cyl(t_cyl *cyl, t_ray *ray)
{
	t_bhaskara	eq;
	t_vec3		diff;

	cyl->caps = 0;

	diff = vector_sub(ray->origin, cyl->center);
	get_discriminant_cyl(cyl, ray, diff, &eq);
	if (eq.discriminant < 0)
		return (0);
	get_bhaskara(&eq);
	
	double t_body;
	int body_hit;
	double h0;
	double h1;
	
	body_hit = 0;
	t_body = INFINITY;

	//////******	t0	******///////
	if (eq.t0 >= EPSILON) //Evitar errores.
	{
		
		h0 = vector_dot_product(vector_add(diff, vector_scale(ray->direction, eq.t0)), cyl->dir); // medida desde la base sobre el eje hasta el hitpoint
	    if (fabs(h0) <= cyl->h / 2) //Si está entre 0 y la altura máxima
		{
	        t_body = eq.t0;	//SI Pertenece, almacenamos ese punto en t_body
	        body_hit = 1;	//Pertenece
	    }
	}
	
	//////******	t1	******///////		t1 es un punto más lejano que t0
	if (eq.t1 >= EPSILON && eq.t1 < t_body)	// si t1 es mayor que t_body, ya tenemos un punto más cercano, por tanto el lejano ya no nos interesa
	{
		h1 = vector_dot_product(vector_add(diff, vector_scale(ray->direction, eq.t1)), cyl->dir);
	    if (fabs(h1) <= cyl->h / 2)
		{
			t_body = eq.t1;
			body_hit = 1;
	    }
	}
	
	// if (body_hit)
	// 	ray->t = t_body;

	// Intersección con las tapas del cilindro
	double t_cap = INFINITY;
	int cap_hit = get_intersect_cy_caps(ray->origin, ray->direction, *cyl, &t_cap);
	
	// calcular la intersección más cercana
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
