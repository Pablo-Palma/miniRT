/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:41:24 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/14 12:55:38 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

static void	old_scene_one(t_scene *scene)
{
	scene->cam = (t_cam)
	{
		.view_point = {0, 0, 10}, // 5 unidades detrás del origen de z.
		.orientation = {0, 0, -1}, // Mirando hacia el frente en el eje Z
		.fov = 90 // Campo de vision de 90 grados.
	};
	scene->sphere = (t_sphere){
		.center = {0, -1, 0},
		.radius = 2 
		//.color = 0xFF5733
	};
	scene->plane = (t_plane)
	{
		.point = {1, -3, 0},
		.normal = {0, 1, 0},
		.color = GREY

	};
	scene->light = (t_light){
		.pos = {-5, 5, 0},	//Posicion
		.brigthness = 0.9	//brillo
	};
}

static void	old_scene_two(t_scene *scene)
{
	scene->cam = (t_cam)
	{
		.view_point = {0, 0, 10}, // 5 unidades detrás del origen de z.
		.orientation = {0, 0, -1}, // Mirando hacia el frente en el eje Z
		.fov = 90 // Campo de vision de 90 grados.
	};

//	double angle = 90.0 * (M_PI / 180.0); // Convertir grados a radianes

    t_vec3 dir =
	{
        .x = 1,  // Componente x del vector de dirección basado en el ángulo
        .y = 0,
        .z = -0.6 // Componente y negativa para que apunte hacia la cámara
    };

	scene->cyl = (t_cyl)
	{
		.center = (t_vec3)
		{
			.x = 0,
			.y = 0,
			.z = 0 
		},
		.dir = normalize(dir),
		.radius = 2,
		.h = 4,
		.color = CIAN
	};
	scene->plane = (t_plane)
	{
		.point = {0, -3, 0},
		.normal = {0, 1, 0},
		.color = GREY

	};

	scene->light = (t_light){
		.pos = {0, 5, 0},	//Posicion
		.brigthness = 0.9	//brillo
	};
}

void	init_scene(t_scene *scene, t_list *obj)
{
	old_scene_two(scene);
	return ;
	old_scene_one(scene);
	old_scene_two(scene);
	scene->cam = *((t_cam *)((t_obj *)objchr(obj, "C")->content)->child);
	scene->light = *((t_light *)((t_obj *)objchr(obj, "L")->content)->child);
	scene->sphere = *((t_sphere *)((t_obj *)objchr(obj, "sp")->content)->child);
	scene->plane = *((t_plane *)((t_obj *)objchr(obj, "pl")->content)->child);
}
