/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:04:07 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/19 17:10:41 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	ray_sum(t_ray *ray, t_vec3 alight)
{
	t_list	*ray_list;
	t_ray	*next_ray;
	t_vec3	pxl_light;
	t_vec3	temp;
	double	diffuse;
	double	specular;
	t_light_params light_params;
	
	pxl_light = (t_vec3){0,0,0};
	ray_list = *ray->next;
	while (ray_list)
	{
		next_ray = ray_list->content;
		if (!*next_ray->obj)
			return (pxl_light);
		if (is_child(*next_ray->obj, "L"))
		{
			temp = color_to_vec(*(*next_ray->obj)->color);
			light_params.norm = normalize(get_normal(*ray->obj, next_ray->origin));
			light_params.view_dir = normalize(ray->direction);
			light_params.light_dir = normalize(next_ray->direction);
			// if (vector_dot_product(norm, vector_sub(ray->origin, ray->direction)) < 0)
			// 	norm = vector_negate(norm);
			diffuse = calculate_diffuse(light_params.light_dir, light_params.norm, ((t_light *)(*next_ray->obj)->child)->brigthness);
			temp = vector_scale(temp, diffuse);
			temp = vector_fmax(temp, alight);
			if (CHECKERBOARD == 0)
				temp = vector_multiply(temp, normalize(color_to_vec(*(*ray->obj)->color)));
			else
				temp = vector_multiply(temp, normalize(color_to_vec(checkerboard(*ray->obj, next_ray->origin))));
			specular = calculate_specular(light_params, 1.0, 100.0);
			temp = vector_add(temp, vector_scale(color_to_vec(*(*next_ray->obj)->color), specular));
			pxl_light = vector_add(pxl_light, temp);
		}
		else if (next_ray->img_trace)
		{
			/*handle reflection*/
			temp = ray_sum(next_ray, alight);
			temp = vector_fmax(temp, alight);
			if (CHECKERBOARD == 0)
				temp = vector_multiply(temp, normalize(color_to_vec(*(*ray->obj)->color)));
			else
				temp = vector_multiply(temp, normalize(color_to_vec(checkerboard(*ray->obj, next_ray->origin))));
			pxl_light = temp;
			//pxl_light = vector_add(pxl_light, temp);
		}
		// else
		// {
		// 	temp = color_to_vec(BLACK);
		// 	temp = vector_fmax(temp, alight);
		// 	temp = vector_multiply(temp, normalize(color_to_vec(*(*ray->obj)->color)));
		// 	temp = color_to_vec(BLACK);
		// 	pxl_light = temp;
		// }
		ray_list = ray_list->next;
	}
	if (vector_cmp(pxl_light, color_to_vec(BLACK)))
	{
		if (CHECKERBOARD == 0)
			pxl_light = vector_multiply(alight, normalize(color_to_vec(*(*ray->obj)->color)));
		else
			pxl_light = vector_multiply(alight, normalize(color_to_vec(checkerboard(*ray->obj, next_ray->origin))));
		// pxl_light = vector_fmax(pxl_light, alight);
		// pxl_light = alight;
	}
	return (pxl_light);
}
