/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:55:48 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/06 13:56:01 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int intersect_ray_sphere(t_vec3 origin, t_vec3 direction, t_sphere sphere, double *t)
{	//Esta funcion determina si un rayo intersecta con un esfera.
    t_vec3 oc = {origin.x - sphere.center.x, origin.y - sphere.center.y, origin.z - sphere.center.z};	//calcula vector desde origen del rayo a centro
	//de la esfera
    double a = direction.x * direction.x + direction.y * direction.y + direction.z * direction.z;
    double b = 2.0 * (oc.x * direction.x + oc.y * direction.y + oc.z * direction.z);
    double c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - sphere.radius * sphere.radius;
    double discriminant = b * b - 4 * a * c; //Discriminant para determinar si hay intersección.

    if (discriminant < 0) {
        return 0; // No intersection
    }

    double t0 = (-b - sqrt(discriminant)) / (2.0 * a);	//Dos posibles solucciones de la ecuación cudarática.
    double t1 = (-b + sqrt(discriminant)) / (2.0 * a);

    // Usamos el valor de t más pequeño positivo como la distnacia al punto de intersección
    if (t0 > 0 && (t0 < *t || *t < 0)) {
        *t = t0;
    } else if (t1 > 0 && (t1 < *t || *t < 0)) {
        *t = t1;
    } else {
        return 0; // No intersection in the positive t direction
    }

    return 1; // Intersection occurred
}
