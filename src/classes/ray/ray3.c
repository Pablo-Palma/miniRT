/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:04:07 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/19 17:31:47 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	handle_ray_to_light(t_raysum *rs, t_ray *ray, t_vec3 *alight)
{
	rs->temp = color_to_vec(*(*rs->next_ray->obj)->color);
	rs->norm = normalize(get_normal(*ray->obj, rs->next_ray->origin));
	rs->view_dir = normalize(ray->direction);
	rs->light_dir = normalize(rs->next_ray->direction);
	rs->diffuse = calculate_diffuse(rs->light_dir, rs->norm,
			((t_light *)(*rs->next_ray->obj)->child)->brigthness);
	rs->temp = vector_scale(rs->temp, rs->diffuse);
	rs->temp = vector_fmax(rs->temp, *alight);
	if (CHECKERBOARD == 0)
		rs->temp = vector_multiply(rs->temp,
				normalize(color_to_vec(*(*ray->obj)->color)));
	else
		rs->temp = vector_multiply(rs->temp,
				normalize(color_to_vec(checkerboard(*ray->obj,
							rs->next_ray->origin))));
	rs->specular = calculate_specular((t_light_params){rs->view_dir,
			rs->light_dir, rs->norm}, 1.0, 100.0);
	rs->temp = vector_add(rs->temp,
			vector_scale(color_to_vec(*(*rs->next_ray->obj)->color),
				rs->specular));
	rs->pxl_light = vector_add(rs->pxl_light, rs->temp);
}

static void	handle_ray_imgdir(t_raysum *rs, t_ray *ray, t_vec3 *alight)
{
	rs->temp = ray_sum(rs->next_ray, *alight);
	rs->temp = vector_fmax(rs->temp, *alight);
	if (CHECKERBOARD == 0)
		rs->temp = vector_multiply(rs->temp,
				normalize(color_to_vec(*(*ray->obj)->color)));
	else
		rs->temp = vector_multiply(rs->temp,
				normalize(color_to_vec(checkerboard(*ray->obj,
							rs->next_ray->origin))));
	rs->pxl_light = rs->temp;
}

static void	handle_shadow(t_raysum *rs, t_ray *ray, t_vec3 *alight)
{
	if (CHECKERBOARD == 0)
		rs->pxl_light = vector_multiply(*alight,
				normalize(color_to_vec(*(*ray->obj)->color)));
	else
		rs->pxl_light = vector_multiply(*alight,
				normalize(color_to_vec(checkerboard(*ray->obj,
							rs->next_ray->origin))));
}

t_vec3	ray_sum(t_ray *ray, t_vec3 alight)
{
	t_raysum	rs;

	rs.pxl_light = (t_vec3){0, 0, 0};
	rs.ray_list = *ray->next;
	while (rs.ray_list)
	{
		rs.next_ray = rs.ray_list->content;
		if (!*rs.next_ray->obj)
			return (rs.pxl_light);
		if (is_child(*rs.next_ray->obj, "L"))
			handle_ray_to_light(&rs, ray, &alight);
		else if (rs.next_ray->img_trace)
			handle_ray_imgdir(&rs, ray, &alight);
		rs.ray_list = rs.ray_list->next;
	}
	if (vector_cmp(rs.pxl_light, color_to_vec(BLACK)))
		handle_shadow(&rs, ray, &alight);
	return (rs.pxl_light);
}
