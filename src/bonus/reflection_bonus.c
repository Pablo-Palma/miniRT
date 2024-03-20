/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:10:38 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/19 19:36:29 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	calculate_reflection(t_vec3	hit_point, t_vec3 normal, t_scene *scene,
	t_vec3 incident_ray)
{
	double	reflectivity = 0.9;
	t_vec3	reflected_ray_dir = reflect(incident_ray, normal);
	int		reflected_color = trace_ray(hit_point, reflected_ray_dir, scene);

	int		base_color = scene->plane.color;
	int		final_color = mix_colors_reflect(reflected_color, base_color, reflectivity);
	return (final_color);
}

int	mix_colors_reflect(int reflected_color, int base_color, double reflectivity)
{
	int	base_red = (base_color >> 16) & 0xFF;
	int	base_green = (base_color >> 8) & 0xFF;
	int	base_blue = base_color & 0xFF;

	int	ref_red = (reflected_color >> 16) & 0xFF;
	int	ref_green = (reflected_color >> 8) & 0xFF;
	int	ref_blue = reflected_color  & 0xFF;

	int	mixed_red = (int)((1 - reflectivity) * base_red + reflectivity * ref_red);
	int	mixed_green = (int)((1 - reflectivity) * base_green + reflectivity * ref_green);
	int	mixed_blue = (int)((1 - reflectivity) * base_blue + reflectivity * ref_blue);
	
	return(mixed_red << 16) | (mixed_green << 8) | mixed_blue;
}


int	trace_ray(t_vec3 origin, t_vec3 dir, t_scene *scene)
{
	int		color = BLACK;
	t_vec3	ray_dir = normalize(dir);
	int		hit_color  = 0;
	double	closest_t = INFINITY;
	double	t = 0;

	if (intersect_ray_sphere(origin, ray_dir, scene->sphere, &t) && t < closest_t)
	{
		closest_t = t;
		hit_color = handle_sphere_intersec(ray_dir, scene, 0, 0, NULL);
		printf("%d\n", hit_color);
	}
	if (intersect_ray_cyl(origin, ray_dir,scene->cyl, &t) && t < closest_t)
	{
		closest_t = t;
		hit_color = handle_cyl_intersec(ray_dir, scene, 0, 0, NULL);
	}
	if (intersect_ray_plane(origin, ray_dir, scene->plane, &t) && t < closest_t)
	{
		closest_t = t;
		hit_color = handle_plane_intersec(ray_dir, scene, 0, 0, NULL);
	}
	if (closest_t < INFINITY)
		color = hit_color;
	return(color);
}
