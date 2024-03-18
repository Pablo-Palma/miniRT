/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 22:08:02 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/18 13:56:13 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	intersect_pl(t_plane plane, t_ray *ray)
{
	double	denom;

	denom = vector_dot_product(ray->direction, plane.normal);
	if (fabs(denom) > 1e-6)
	{
		t_vec3	origin_plane = vector_sub(plane.point, ray->origin);
		ray->t = vector_dot_product(origin_plane, plane.normal) / denom;
		return(ray->t >= 0);
	}
	return (0);
}

static int intersect_sp(t_sphere sphere, t_ray *ray)
{
	t_vec3 oc = {ray->origin.x - sphere.center.x, ray->origin.y - sphere.center.y, ray->origin.z - sphere.center.z};
	double a = vector_dot_product(ray->direction, ray->direction);
	double b = 2.0 * vector_dot_product(oc, ray->direction);
	double c = vector_dot_product(oc, oc) - sphere.radius * sphere.radius;
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	    return 0;
	double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t0 > 0 && (t0 < ray->t || ray->t < 0))
	    ray->t = t0;
	else if (t1 > 0 && (t1 < ray->t || ray->t < 0))
	    ray->t = t1;
	else 
	    return 0;
	return 1;
}

static int	get_intersect_cy_caps(t_vec3 origin, t_vec3 dir, t_cyl cyl, double *t_cap)
{
	t_vec3	cap_normal = cyl.dir;
	double	cap_t[2] = {INFINITY, INFINITY};
	int		hit = 0;
	int		i = 0;
	double	sign = 1.0;

	while(i < 2)
	{
		if (i == 1)
			sign = -1.0;
		t_vec3	cap_center = vector_add(cyl.center, vector_scale(cap_normal, sign * cyl.h * 0.00));
		double d = vector_dot_product(vector_sub(cap_center, origin), cap_normal) / vector_dot_product(dir, cap_normal);
		if (d >= 0 && d < *t_cap)
		{
			t_vec3	p = vector_add(origin, vector_scale(dir, d));
			double	distance = vector_length(vector_sub(p, cap_center));
			if (distance <= cyl.radius)
			{
				cap_t[i] = d;
				hit = 1;
			}
		}
		i++;
	}

	if (hit)
	{
		double	closest_t = cap_t[0];
		if (cap_t[1] < cap_t[0])
			closest_t = cap_t[1];
		*t_cap = closest_t;
	}
	return(hit);


}

static int	intersect_cyl(t_cyl cyl, t_ray *ray)
{
	t_vec3 diff = vector_sub(ray->origin, cyl.center);
	t_vec3 dir_cross_cyl_dir = vector_cross(ray->direction, cyl.dir); //Cruz entre el rayo y el cilindro
	t_vec3 diff_cross_cyl_dir = vector_cross(diff, cyl.dir); // Cruz entre diff y el cilindro
	
	double a = vector_dot_product(dir_cross_cyl_dir, dir_cross_cyl_dir); // Cuadrado del cruz de direcciones (rayo x cilindro)
	double b = 2 * vector_dot_product(dir_cross_cyl_dir, diff_cross_cyl_dir); // 2 producto punto  ((cruz de rayo-cilindor) * (cruz de diff-cilindro))
	double c = vector_dot_product(diff_cross_cyl_dir, diff_cross_cyl_dir) - (cyl.radius * cyl.radius); //cuadrado de (cruz de diff-cilindro) - (radio^2)
	
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	    return 0; // No intersection
	
	double sqrt_discriminant = sqrt(discriminant);
	double t0 = (-b - sqrt_discriminant) / (2 * a);		//Distancia desde el rayo al primer punto de interseccion
	double t1 = (-b + sqrt_discriminant) / (2 * a);		//Distancia desde el rayo al segundo punto de interseccion
	
	double t_body = INFINITY;
	int body_hit = 0;
	//////******	t0	******///////
	if (t0 >= EPSILON) //Evitar errores.
	{
	    double h0 = vector_dot_product(vector_add(diff, vector_scale(ray->direction, t0)), cyl.dir); // medida desde la base sobre el eje hasta el hitpoint
	    if (h0 >= 0 && h0 <= cyl.h) //Si está entre 0 y la altura máxima
		{
	        t_body = t0;	//SI Pertenece, almacenamos ese punto en t_body
	        body_hit = 1;	//Pertenece
	    }
	}
	
	//////******	t1	******///////		t1 es un punto más lejano que t0
	if (t1 >= EPSILON && t1 < t_body)	// si t1 es mayor que t_body, ya tenemos un punto más cercano, por tanto el lejano ya no nos interesa
	{
	    double h1 = vector_dot_product(vector_add(diff, vector_scale(ray->direction, t1)), cyl.dir);
	    if (h1 >= 0 && h1 <= cyl.h)
		{
			t_body = t1;
			body_hit = 1;
	    }
	}
	
	// Intersección con las tapas del cilindro
	double t_cap = INFINITY;
	int cap_hit = get_intersect_cy_caps(ray->origin, ray->direction, cyl, &t_cap);
	
	// calcular la intersección más cercana
	if (cap_hit && (t_cap < t_body || !body_hit))
	{
		ray->t = t_cap;
		return 1;
	}
	else if (body_hit)
	{
		ray->t = t_body;
		return 1;
	}
	return 0;
}


//change values on ray.obj and ray.t seting the obj intercaction and value of t on parametrized line/vector
void intersect(t_list *obj, t_ray *ray)
{
	int	ret;

	ret = 0;
    if (!ft_strncmp(((t_obj *)(obj->content))->line, "pl", 2))
        ret = intersect_pl(*(t_plane *)(((t_obj *)(obj->content))->child), ray);
    else if (!ft_strncmp(((t_obj *)(obj->content))->line, "sp", 2))
        ret = intersect_sp(*(t_sphere *)(((t_obj *)(obj->content))->child), ray);
	else if (!ft_strncmp(((t_obj *)(obj->content))->line, "cy", 2))
        ret = intersect_cyl(*(t_cyl *)(((t_obj *)(obj->content))->child), ray);
	if (ret)
		ray->obj = (t_obj *)obj->content;
}