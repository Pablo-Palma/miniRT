/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:41:24 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/06 15:03:13 by pabpalma         ###   ########.fr       */
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
		.center = {0, 0, 0},
		.radius = 3 
		//.color = 0xFF5733
	};
	scene->plane = (t_plane)
	{
		.point = {0, -1, 0},
		.normal = {0, 1, 0},
		.color = GREY

	};
	scene->light = (t_light){
		.pos = {2, 2, 5},	//Posicion
		.brigthness = 0.9	//brillo
	};
}
