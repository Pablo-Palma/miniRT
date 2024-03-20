/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_trace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 07:36:23 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/19 21:42:22 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static int	trace_light_sp(t_list *obj, t_ray *ray)
{
	t_ambient_light ambient_light = *(t_ambient_light *)((t_obj *)objchr(obj, "A")->content)->child;
	t_light			light = *((t_light *)((t_obj *)objchr(obj, "L")->content)->child);

	t_vec3	view_dir;
	t_vec3	light_dir;
	double	diffuse = 0.0;
	double	specular = 0.0;

	t_vec3	point = ((t_ray *)ray->next->content)->origin;
	t_vec3	norm = get_normal((t_list *)*(ray->obj), point);
	light_dir = normalize(vector_negate(((t_ray *)ray->next->content)->direction));
	view_dir = normalize(vector_negate(ray->direction));
	diffuse = calculate_diffuse(light_dir, norm, light.brigthness);
	specular = calculate_specular(view_dir, light_dir, norm, 0.01, 100000.0);
	// int	shadowed = shadow(scene, point, light, norm);
	// if (!shadowed)
	// {
	// 	diffuse = calculate_diffuse(light_dir, norm, light.brigthness);
	// 	specular = calculate_specular(view_dir, light_dir, norm, 1.0, 10.0);
	// }
	// else
	// {
	// 	diffuse = 0.0;
	// 	specular = 0.0;
	// }
	int	color = mix_colors(ambient_light, CIAN /*sphere.color*/, diffuse, specular);
	return (color);
}

static int	trace_light_pl(t_list *obj, t_ray *ray)
{
	(void)ray;
	t_ambient_light ambient_light = *(t_ambient_light *)((t_obj *)objchr(obj, "A")->content)->child;
	// t_plane		plane = *(t_plane *)((t_obj *)(obj->content))->child;
	// t_cam		cam = *((t_cam *)((t_obj *)objchr(obj, "C")->content)->child);
	// t_light		light = *((t_light *)((t_obj *)objchr(obj, "L")->content)->child);
	// int	color;
	// t_vec3	hit_point;
	// t_vec3	normal;
	// t_vec3	view_dir;
	// hit_point = vector_add(cam.view_point, vector_scale(ray.direction, ray.t));
	// normal = plane.normal;//**Diferencia2
	// view_dir = vector_negate(ray.direction);


	// t_vec3	light_dir;
	// light_dir = normalize(vector_sub(light.pos, hit_point));
	// double	diffuse;
	// double	specular;
	double	diffuse = 0.0;
	double	specular = 0.0;
	// int	shadowed;
	//shadowed = shadow_plane(scene, hit_point);
	// if (!shadowed)
	// {
	// 	diffuse = calculate_diffuse(light_dir, normal, light.brigthness);
	// 	specular = calculate_specular(view_dir, light_dir, normal, 1.0, 10.0);
	// }
	// else
	// {
	// 	diffuse = 0.0;
	// 	specular = 0.0;
	// }
	//double	ambient = 0.1;
	int	color = mix_colors(ambient_light, WHITE, diffuse, specular);
	return (color);
}

static t_vec3	get_cylinder_normal(t_vec3 hit_point, t_cyl cyl)
{
	t_vec3 center_to_hit = vector_sub(hit_point, cyl.center);
	double proj_length = vector_dot_product(center_to_hit, cyl.dir);
	t_vec3 proj_point = vector_add(cyl.center, vector_scale(cyl.dir, proj_length));
	t_vec3 normal = vector_sub(hit_point, proj_point);
	return normalize(normal);
}

static int	trace_light_cyl(t_list *obj, t_ray *ray)
{
	t_cyl	cyl = *(t_cyl *)((t_obj *)(obj->content))->child;
	t_cam	cam = *((t_cam *)((t_obj *)objchr(obj, "C")->content)->child);
	t_light	light = *((t_light *)((t_obj *)objchr(obj, "L")->content)->child);
	t_vec3	ray_origin = cam.view_point;
	t_vec3	hit_point = vector_add(ray_origin, vector_scale(ray->direction, ray->t));
	t_vec3	normal = get_cylinder_normal(hit_point, cyl);
	t_vec3 light_dir = normalize(vector_sub(light.pos, hit_point));


	t_ambient_light ambient_light = *(t_ambient_light *)((t_obj *)objchr(obj, "A")->content)->child;
	double diffuse = calculate_diffuse(light_dir, normal, light.brigthness);
	t_vec3 view_dir = normalize(vector_sub(cam.view_point, hit_point));
	double specular = calculate_specular(view_dir, light_dir, normal, 1.0, 10.0); // Intensidad y brillo arbitrarios
	int color = mix_colors(ambient_light, cyl.color, diffuse, specular); // Ambient light contribution set to 0.1 arbitrarily
	return (color);
}

//trace ray from bj to lightand change values ray.obj and ray.t
int trace_light(t_list *obj, t_ray *ray)
{
    int (*fptr)(t_list *, t_ray *) = NULL;

	if (!ft_strncmp(((t_obj *)(obj->content))->line, "pl", 2))
        fptr = trace_light_pl;
    else if (!ft_strncmp(((t_obj *)(obj->content))->line, "sp", 2))
        fptr = trace_light_sp;
	else if (!ft_strncmp(((t_obj *)(obj->content))->line, "cy", 2))
        fptr = trace_light_cyl;
    else
		return (0);
    return fptr(obj, ray);
}