/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:22:42 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/17 12:28:16 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vector_dot_product(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vector_negate(t_vec3 v)
{
	return ((t_vec3){-v.x, -v.y, -v.z});
}

t_vec3	vector_cross(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){
		.x = v1.y * v2.z - v1.z * v2.y,
		.y = v1.z * v2.x - v1.x * v2.z,
		.z = v1.x * v2.y - v1.y * v2.x,
	});
}

t_vec3	vector_projection(t_vec3 v, t_vec3 u)
{
	double	dot_product;
	double	u_magnitude_squared;
	t_vec3	projection;

	dot_product = vector_dot_product(v, u);
	u_magnitude_squared = vector_dot_product(u, u);
	projection = vector_scale(u, dot_product / u_magnitude_squared);
	return (projection);
}

t_vec3	vector_reflect(t_vec3 v, t_vec3 n)
{
	double	dot;

	dot = vector_dot_product(v, n);
	return ((t_vec3){
		v.x - 2 * dot * n.x,
		v.y - 2 * dot * n.y,
		v.z - 2 * dot * n.z,
	});
}
