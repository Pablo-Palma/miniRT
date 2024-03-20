/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:26:07 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/20 16:43:59 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cap_uv(t_vec3 hit_point, t_cyl cyl, double *u, double *v)
{
	t_vec3 point_vector = vector_sub(hit_point, cyl.center);
    double angle = atan2(point_vector.z, point_vector.x);
    *u = (angle + M_PI) / (2 * M_PI);  // Coordenada U basada en el ángulo

    // La coordenada V debe ser proporcional a la distancia al centro de la tapa
    double distance_to_center = vector_length(point_vector);
    *v = distance_to_center / cyl.radius;  // De 0 en el centro a 1 en el borde

    // Escalado de U y V para que coincidan con las divisiones del cuerpo
    *u *= (cyl.h / cyl.radius);  // Ajustar según el número de cuadrados en el cuerpo
    *v *= (cyl.h / cyl.radius);  // Ajustar según el número de cuadrados en el cuerpo

    *u = fmod(*u, 1.0);  // Asegurar que U está en el rango [0, 1]
    *v = fmod(*v, 1.0);  // Asegurar que V está en el rango [0, 1]
}
