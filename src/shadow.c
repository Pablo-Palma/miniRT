/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:26:08 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/09 11:47:53 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double vector_length(t_vec3 v) {
    return sqrt(vector_dot_product(v, v));
}

int shadow_plane(t_scene *scene, t_vec3 hit_point)
{
	t_vec3 light_direction = vector_sub(scene->light.pos, hit_point);
    double light_distance = vector_length(light_direction);
    light_direction = normalize(light_direction);

    t_vec3 origin_offset = vector_add(hit_point, vector_scale(light_direction, 0.001)); // Evitar la auto-intersección
    double t = INFINITY;

    if (intersect_ray_sphere(origin_offset, light_direction, scene->sphere, &t)) {
        if (t < light_distance) {
            return 1; // El punto está en sombra
        }
    }
    return 0; // El punto no está en sombra
}

int	shadow(t_scene *scene, t_vec3 hit_point, t_light light, t_vec3 normal)
{
	t_vec3 to_light = vector_sub(light.pos, hit_point); // Vector del punto de intersección hacia la fuente de luz.
	double	distance = sqrt(vector_dot_product(to_light, to_light)); // Distancia a la fuente de luz.
	t_vec3	light_dir = normalize(to_light); //Dirección normalizada.
	t_vec3	origin_offset = vector_add(hit_point, vector_scale(normal, 0.0001)); //Ajustar punto de origen y evitar auto-intersección.
	double	t = INFINITY;

	if (intersect_ray_sphere(origin_offset, light_dir, scene->sphere, &t))
	{
		if (t < distance)
			return (1);
	}
	return (0);
}
