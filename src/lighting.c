/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:50:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/05 12:40:02 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	VECTORIAL FUNCS

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	double	dot;

	dot = vector_dot_product(v, n);
	return (t_vec3){
		v.x - 2 * dot * n.x,
		v.y - 2 * dot * n.y,
		v.z - 2 * dot * n.z,
	};
}

int	shadow(t_scene *scene, t_vec3 hit_point, t_light light)
{
	t_vec3 to_light = vector_sub(light.pos, hit_point); // Vector del punto de intersección hacia la fuente de luz.
	double	distance = sqrt(vector_dot_product(to_light, to_light)); // Distancia a la fuente de luz.
	t_vec3	light_dir = normalize(to_light); //Dirección normalizada.
	t_vec3	origin_offset = vector_add(hit_point, vector_scale(light_dir, 0.0001)); //Ajustar punto de origen y evitar auto-intersección.
	double	t = INFINITY;

	if (intersect_ray_sphere(origin_offset, light_dir, scene->sphere, &t))
	{
		if (t < distance)
			return (1);
	}
	return (0);
}

double	calculate_diffuse(t_vec3 light_dir, t_vec3	normal, double light_brightness)
{
	double	dot;

	dot = fmax(vector_dot_product(normal, light_dir), 0.0);
	return (dot * light_brightness);
}

double	calculate_specular(t_vec3 view_dir, t_vec3 light_dir, t_vec3 normal, double intensity, double shine)
{
	t_vec3	reflect_dir;
	double	spec;

	reflect_dir = reflect(vector_negate(light_dir), normal);
	spec = pow(fmax(vector_dot_product(view_dir, reflect_dir), 0.0), shine);
	return (intensity * spec);
}
