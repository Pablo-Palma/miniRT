/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:41:24 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/09 12:36:33 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	init_scene(t_scene *scene)
{
	scene->cam = (t_cam){
		.view_point = {0, 0, 10}, // 5 unidades detrás del origen de z.
		.orientation = {0, 0, 1}, // Mirando hacia el frente en el eje Z
		.fov = 90 // Campo de vision de 90 grados.
	};
	scene->sphere = (t_sphere){
		.center = {0, -1, 0},
		.radius = 2 
		//.color = 0xFF5733
	};
	scene->plane = (t_plane)
	{
		.point = {0, -3, 0},
		.normal = {0, 1, 0},
		.color = GREY

	};
	scene->light = (t_light){
		.pos = {5, 10, 5},	//Posicion
		.brigthness = 0.7	//brillo
	};
}
