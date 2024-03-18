/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 14:03:29 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/18 14:36:12 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include "checkerboard.h"

int	intersect_ray_plane(t_vec3 ray_origin, t_vec3 ray_dir, t_plane plane, double *t)
{
	double	denom;

	denom = vector_dot_product(ray_dir, plane.normal);
	if (fabs(denom) > 1e-6)
	{
		t_vec3	origin_plane = vector_sub(plane.point, ray_origin);
		*t = vector_dot_product(origin_plane, plane.normal) / denom;
		return(*t >= 0);
	}
	return (0);
}

int	handle_plane_intersec(t_vec3 ray_dir, t_scene *scene, int x, int y, t_graph *graph)
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
	int		base_color = WHITE;
	//double	ambient = 0.1;
	if (intersect_ray_plane(scene->cam.view_point, ray_dir, scene->plane, &t)) //**Dieferencia1
	{
		hit_point = vector_add(scene->cam.view_point, vector_scale(ray_dir, t));
		normal = scene->plane.normal;//**Diferencia2
		light_dir = normalize(vector_sub(scene->light.pos, hit_point));
		view_dir = vector_negate(ray_dir);
		shadowed = shadow_plane(scene, hit_point);
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
		if(scene->checkerboard)
			base_color = apply_checkerboard_texture(hit_point);
		color = mix_colors(base_color, diffuse, specular, *scene);
		put_pixel_to_image(graph, x, y, color);
		return (1);
	}
	return (0);
}
