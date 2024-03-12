/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:55:48 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/09 19:13:30 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int intersect_ray_sphere(t_vec3 origin, t_vec3 direction, t_sphere sphere, double *t)
{	//Esta funcion determina si un rayo intersecta con un esfera.
	t_vec3 oc = {origin.x - sphere.center.x, origin.y - sphere.center.y, origin.z - sphere.center.z};	//calcula vector desde origen del rayo a centro
	//de la esfera
	double a = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
	double b = 2.0 * (oc.x * direction.x + oc.y * direction.y + oc.z * direction.z);
	double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere.radius * sphere.radius;
	double discriminant = b * b - 4 * a * c; //Discriminant para determinar si hay intersección.
	
	if (discriminant < 0)
	    return 0; // No intersection
	
	double t0 = (-b - sqrt(discriminant)) / (2.0 * a);	//Dos posibles solucciones de la ecuación cudarática.
	double t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	
	// Usamos el valor de t más pequeño positivo como la distnacia al punto de intersección
	if (t0 > 0 && (t0 < *t || *t < 0))
	    *t = t0;
	else if (t1 > 0 && (t1 < *t || *t < 0))
	    *t = t1;
	else 
	    return 0; // No intersection in the positive t direction
	return 1; // Intersection occurred
}

int	handle_sphere_intersec(t_vec3	ray_dir, t_scene *scene, int x, int y, t_graph *graph)
{
	int	shadowed;
	int	color;
	t_vec3	hit_point;
	t_vec3	normal;
	t_vec3	light_dir;
	t_vec3	view_dir;
	double	diffuse;
	double	specular;
	double	t = 10000000;
	double	ambient = 0.1;
	if (intersect_ray_sphere(scene->cam.view_point, ray_dir, scene->sphere, &t)) // Verificar si el rayo intersecta con la esfera
	{
		hit_point = vector_add(scene->cam.view_point, vector_scale(ray_dir, t));
		normal = normalize(vector_sub(hit_point, scene->sphere.center));
		light_dir = normalize(vector_sub(scene->light.pos, hit_point));
		view_dir = vector_negate(ray_dir);
		shadowed = shadow(scene, hit_point, scene->light, normal);
		if (!shadowed)
		{
			diffuse = calculate_diffuse(light_dir, normal, scene->light.brigthness);
			specular = calculate_specular(view_dir, light_dir, normal, 1.0, 10.0);
		}
		else
		{
			diffuse = 0.0;
			specular = 0.0;
		}
		color = mix_colors(CIAN, diffuse, specular, ambient);
		put_pixel_to_image(graph, x, y, color);
		return (1);
	}
	return (0);
}
