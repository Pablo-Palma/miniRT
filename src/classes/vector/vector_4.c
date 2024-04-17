/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:25:46 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/17 12:37:29 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	vec_to_color(t_vec3 vec)
{
	int	r;
	int	g;
	int	b;

	r = (int)fmin(255.0, fmax(0.0, vec.x));
	g = (int)fmin(255.0, fmax(0.0, vec.y));
	b = (int)fmin(255.0, fmax(0.0, vec.z));
	return ((r << 16) | (g << 8) | b);
}

t_vec3	normalize(t_vec3 v)
{
	double	len;
	t_vec3	normalized;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	normalized.x = v.x / len;
	normalized.y = v.y / len;
	normalized.z = v.z / len;
	return (normalized);
}
t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	double	dot;

	dot = vector_dot_product(v, n);
	return ((t_vec3){
		v.x - 2 * dot * n.x,
		v.y - 2 * dot * n.y,
		v.z - 2 * dot * n.z,
	});
}
