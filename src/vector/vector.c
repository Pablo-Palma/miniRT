/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:42:08 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/30 20:09:34 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


double vector_length(t_vec3 v)
{
    return sqrt(vector_dot_product(v, v));
}

t_vec3	vector_scale(t_vec3 v, double s)
{
	return (t_vec3){v.x * s,  v.y * s, v.z * s};
}

t_vec3	vector_add(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

t_vec3	vector_sub(t_vec3 v1, t_vec3 v2)
{
	return (t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

t_vec3	vector_multiply(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

double	vector_dot_product(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vector_negate(t_vec3 v)
{
	return ((t_vec3){-v.x, -v.y, -v.z});
}

t_vec3	vector_cross(t_vec3 v1, t_vec3	v2)
{
	return ((t_vec3){
	.x = v1.y * v2.z - v1.z * v2.y,
	.y = v1.z * v2.x - v1.x * v2.z,
	.z = v1.x * v2.y - v1.y * v2.x,
	});
}

t_vec3 vector_projection(t_vec3 v, t_vec3 u)
{
    double dot_product;
    double u_magnitude_squared;
    t_vec3 projection;

	dot_product = vector_dot_product(v, u);
	u_magnitude_squared = vector_dot_product(u, u);
	projection = vector_scale(u, dot_product / u_magnitude_squared);
    return (projection);
}

t_vec3 color_to_vec(int color)
{
    t_vec3 vec;
    
    vec.x = (double)((color >> 16) & 0xFF);
    vec.y = (double)((color >> 8) & 0xFF);
    vec.z = (double)(color & 0xFF);
    return vec;
}

int vec_to_color(t_vec3 vec)
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
	double	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z); // Calculamos la longitud(magnitud) del vector v con la formula eucladiana
	t_vec3	normalized;	//dividimos cada componente del vector por su logitud, manteniendo la dirección del vector original pero ajustando
	normalized.x = v.x / len;	//su magnitud a 1.
	normalized.y = v.y / len;
	normalized.z = v.z / len;
	return (normalized);
}
