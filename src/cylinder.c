/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:28:25 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/08 14:26:27 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h" 

t_vec3	cylinder_normal(t_cyl cyl, t_vec3 hit_point)
{
	t_vec3 to_hit_point = vector_sub(hit_point, cyl.center);
	double	t = vector_dot_product(to_hit_point, cyl.dir);
	t_vec3	on_axis = vector_add(cyl.center, vector_scale(cyl.dir, t));
	t_vec3	normal = vector_sub(hit_point, on_axis);
	return(normalize(normal));
}

int	intersec_ray_cyl(t_vec3 origin, t_vec3 dir, t_cyl cyl, double *t)
{
	t_vec3	diff = vector_sub(origin, cyl.center);
	double	a = vector_dot_product(dir, dir) - pow(vector_dot_product(dir, cyl.dir), 2);
	double	b = 2 * (vector_dot_product(dir, diff) - (vector_dot_product(dir, cyl.dir) * vector_dot_product(diff, cyl.dir)));
	double	c =  vector_dot_product(diff, diff) - pow(vector_dot_product(diff, cyl.dir), 2) + pow(cyl.radius, 2);
	double	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return(0);
	double	sqrt_discriminant = sqrt(discriminant);
	double	t0 = (-b - sqrt_discriminant) / (2 * a);
	double	t1 = (-b + sqrt_discriminant) / (2 * a);
	if (t0 > 0 && t0 < *t)
	{
		*t = t0;
		return(1);
	}
	if(t1 > 0 && t1 < *t)
	{
		*t = t1;
		return(1);
	}
	return(0);
}

int	handle_cyl_intersec(t_vec3	ray_dir, t_scene *scene, int x, int y, t_graph *graph)
{
	double t = 10000000;
	int	color;

	if(intersec_ray_cyl(scene->cam.view_point, ray_dir, scene->cyl, &t))
	{
		t_vec3	hit_point = vector_add(scene->cam.view_point, vector_scale(ray_dir, t));
		t_vec3	normal = cylinder_normal(scene->cyl, hit_point);
		t_vec3	light_dir = normalize(vector_sub(scene->light.pos, hit_point));
		double	diffuse = calculate_diffuse(light_dir, normal, scene->light.brigthness);
//		t_vec3	reflect_dir = reflect(vector_negate(light_dir), normal);
		double	specular = calculate_specular(ray_dir, light_dir, normal, 1.0, 10.0);
		int		shadowed = shadow(scene, hit_point, scene->light);
		if (shadowed)
		{
			diffuse *= 0.5;
			specular = 0;
		}
		color = mix_colors(scene->cyl.color, diffuse, specular, 0.1);
		put_pixel_to_image(graph, x, y, color);
		return(1);
	}
	return(0);
}
