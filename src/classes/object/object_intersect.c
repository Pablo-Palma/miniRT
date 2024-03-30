/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:28:25 by pabpalma          #+#    #+#             */
	/*   Updated: 2024/03/30 15:33:54 by math             ###   ########.fr       */
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
	t_vec3 oc = vector_sub(ray->origin, sphere.center);
	double a = vector_dot_product(ray->direction, ray->direction);
	double b = 2.0 * vector_dot_product(oc, ray->direction);
	double c = vector_dot_product(oc, oc) - sphere.radius * sphere.radius;
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	    return 0;
	double t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	if (t0 > 0 && t0 < ray->t)
	    ray->t = t0;
	else if (t1 > 0 && t1 < ray->t)
	    ray->t = t1;
	else
	    return 0;
	return 1;
}

// static int	get_intersect_cy_caps(t_vec3 origin, t_vec3 dir, t_cyl cyl, double *t_cap)
// {
// 	t_vec3	cap_normal = cyl.dir;
// 	double	cap_t[2] = {INFINITY, INFINITY};
// 	int		hit = 0;
// 	int		i = 0;
// 	double	sign = 1.0;

// 	while(i < 2)
// 	{
// 		t_vec3	cap_center = vector_add(cyl.center, vector_scale(cap_normal, sign * (cyl.h / 2)));
// 		double d = vector_dot_product(vector_sub(cap_center, origin), cap_normal) / vector_dot_product(dir, cap_normal);
// 		if (d >= 0 && d < *t_cap)
// 		{
// 			t_vec3	p = vector_add(origin, vector_scale(dir, d));
// 			double	distance = vector_length(vector_sub(p, cap_center));
// 			if (distance <= cyl.radius)
// 			{
// 				cap_t[i] = d;
// 				hit = 1;
// 			}
// 		}
// 		i++;
// 		sign = -sign;
// 	}

// 	if (hit)
// 	{
// 		double	closest_t = cap_t[0];
// 		if (cap_t[1] < cap_t[0])
// 			closest_t = cap_t[1];
// 		*t_cap = closest_t;
// 	}
// 	return(hit);


// }

static int	intersect_cyl(t_cyl cyl, t_ray *ray)
{
	t_vec3 diff = vector_sub(ray->origin, cyl.center);	//	vecot Origen-centro cilindro
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
	    if (fabs(h0) <= cyl.h / 2) //Si está entre 0 y la altura máxima
		{
	        t_body = t0;	//SI Pertenece, almacenamos ese punto en t_body
	        body_hit = 1;	//Pertenece
	    }
	}
	
	//////******	t1	******///////		t1 es un punto más lejano que t0
	if (t1 >= EPSILON && t1 < t_body)	// si t1 es mayor que t_body, ya tenemos un punto más cercano, por tanto el lejano ya no nos interesa
	{
	    double h1 = vector_dot_product(vector_add(diff, vector_scale(ray->direction, t1)), cyl.dir);
	    if (fabs(h1) <= cyl.h / 2)
		{
			t_body = t1;
			body_hit = 1;
	    }
	}
	
	if (body_hit)
		ray->t = t_body;

	// Intersección con las tapas del cilindro
	// double t_cap = INFINITY;
	// int cap_hit = get_intersect_cy_caps(ray->origin, ray->direction, cyl, &t_cap);
	
	// calcular la intersección más cercana
	// if (cap_hit && (t_cap < t_body || !body_hit))
	// {
	// 	ray->t = t_cap;
	// 	return 1;
	// }
	// else if (body_hit)
	// {
	// 	ray->t = t_body;
	// 	return 1;
	// }
	return body_hit;
}

int intersect_light(t_light light, t_ray *ray)
{
	t_sphere	light_space;

	light_space.center = light.pos;
	light_space.radius = 0.001;
	return (intersect_sp(light_space,  ray));
}

int intersect_circle(t_circle circle, t_ray *ray)
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



//change values on ray.obj and ray.t seting the obj intercaction and value of t on parametrized line/vector
void intersect(t_obj *obj, t_ray *ray)
{
	int	ret;

	ret = 0;
    if (is_child(obj, "pl"))
        ret = intersect_pl(*(t_plane *)(obj->child), ray);
    else if (is_child(obj, "sp"))
        ret = intersect_sp(*(t_sphere *)(obj->child), ray);
	else if (is_child(obj, "cy"))
        ret = intersect_cyl(*(t_cyl *)(obj->child), ray);
	else if (is_child(obj, "L"))
        ret = intersect_light(*(t_light *)(obj->child), ray);
	else if (is_child(obj, "ci"))
        ret = intersect_circle(*(t_circle *)(obj->child), ray);
	if (ret)
	{
		*ray->obj = obj;
		//printf("line:%s\n", ((t_obj *)(((t_list *)(*ray->obj))->content))->line);
	}
}