/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:26:00 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/17 12:29:05 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vector_fmax(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		.x = fmax(v1.x, v2.x),
		.y = fmax(v1.y, v2.y),
		.z = fmax(v1.z, v2.z)});
}

t_vec3	vector_fmin(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		.x = fmin(v1.x, v2.x),
		.y = fmin(v1.y, v2.y),
		.z = fmin(v1.z, v2.z)});
}

t_vec3	vector_proportion(t_vec3 v1, t_vec3 v2, double percent)
{
	return (vector_add(vector_scale(v1, percent), vector_scale(v2, 1.0
				- percent)));
}

bool	vector_cmp(t_vec3 v1, t_vec3 v2)
{
	return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}

t_vec3	color_to_vec(int color)
{
	t_vec3	vec;

	vec.x = (double)((color >> 16) & 0xFF);
	vec.y = (double)((color >> 8) & 0xFF);
	vec.z = (double)(color & 0xFF);
	return (vec);
}
