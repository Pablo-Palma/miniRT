/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:50:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/19 13:28:55 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	calculate_diffuse(t_vec3 light_dir, t_vec3	normal,
	double light_brightness)
{
	double	dot;

	dot = fmax(vector_dot_product(normal, light_dir), 0.0);
	return (dot * light_brightness);
}

double	calculate_specular(t_light_params params, double intensity,
	double shine)
{
	t_vec3	reflect_dir;
	double	spec;

	reflect_dir = reflect(vector_negate(params.light_dir), params.norm);
	spec = pow(fmax(vector_dot_product(vector_negate(params.view_dir),
					reflect_dir), 0.0), shine);
	return (intensity * spec);
}
