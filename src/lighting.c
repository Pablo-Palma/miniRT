/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:50:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/08 18:18:31 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

//	VECTORIAL FUNCS

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	double	dot;

	dot = vector_dot_product(v, n);
	return (t_vec3){
		v.x - 2 * dot * n.x,
		v.y - 2 * dot * n.y,
		v.z - 2 * dot * n.z,
	};
}

double	calculate_diffuse(t_vec3 light_dir, t_vec3	normal, double light_brightness)
{
	double	dot;

	dot = fmax(vector_dot_product(normal, light_dir), 0.0);
	return (dot * light_brightness);
}

double	calculate_specular(t_vec3 view_dir, t_vec3 light_dir, t_vec3 normal, double intensity, double shine)
{
	t_vec3	reflect_dir;
	double	spec;

	reflect_dir = reflect(vector_negate(light_dir), normal);
	spec = pow(fmax(vector_dot_product(view_dir, reflect_dir), 0.0), shine);
	return (intensity * spec);
}
