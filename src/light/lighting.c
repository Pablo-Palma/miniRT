/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:50:06 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/14 12:55:38 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

//	VECTORIAL FUNCS
//**dot es el producto punto entre el vector incidente v y la normal
//**lo usamos para calcular la dirección del vector reflejado
//**Que calculamos como (v - 2 * dot * n) siguiendo la formula de reflexión
t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	double	dot;

	dot = vector_dot_product(v, n);
	return (t_vec3)
	{
		v.x - 2 * dot * n.x,
		v.y - 2 * dot * n.y,
		v.z - 2 * dot * n.z,
	};
}
/*** la luz difusa depende del ángulo entre la normal de la superficie y la dirección de la luz
	
*/
double	calculate_diffuse(t_vec3 light_dir, t_vec3	normal, double light_brightness)
{
	double	dot;

	dot = fmax(vector_dot_product(normal, light_dir), 0.0); //fmax 0.0 asegura que no sea negativo
	return (dot * light_brightness);
}
/*
	Depende del angulo entre la view.dir y la dirección de la luz reflejada
	shine es el ocmponente de brillo(tamaño y concentración del brillo especular).

*/
double	calculate_specular(t_vec3 view_dir, t_vec3 light_dir, t_vec3 normal, double intensity, double shine)
{
	t_vec3	reflect_dir;
	double	spec;

	reflect_dir = reflect(vector_negate(light_dir), normal);	//	Dirección de reflexion de la luz.
	spec = pow(fmax(vector_dot_product(view_dir, reflect_dir), 0.0), shine);	//Componente especular(view_dir * reflect_dir) ^ shine.
	return (intensity * spec);//luz especular por intensidad de la luz.
}
