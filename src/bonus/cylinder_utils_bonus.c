/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 20:26:07 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/21 11:12:32 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cap_uv(t_vec3 hit_point, t_cyl cyl, double *u, double *v)
{
	t_vec3 local_point = vector_sub(hit_point, cyl.center); // Convertir a coordenadas locales de la tapa
	*u = (local_point.x / cyl.radius + 1) / 2; // Normalizar entre 0 y 1
	*v = (local_point.y / cyl.radius + 1) / 2;
}
