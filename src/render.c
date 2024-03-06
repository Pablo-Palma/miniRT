/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/06 15:02:51 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	compute_ray_dir(int x, int y, t_cam cam)
{
	double	fov_rad = cam.fov * M_PI / 180.0;	//Lo convertimo a Radianes para poder utilizar funciones trigonométricas.
	// (para converir a radian = alguno del campo de vision * pi / 180)
	double	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT; //relacción aspecto, (ancho venta / alto ventana), MANTENER ESCALA.
	double	scale = tan(fov_rad / 2.0);	//tamaño de imagen a escala
	//CALCULAR LAS CORDENADAS EN EL ESPACIO DE LA IMAGEN-----
	double	image_x = (2 * (x + 0.5) / (double)WIN_WIDTH - 1) * aspect_ratio * scale; //
	double	image_y = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT) * scale;
	//-----------
	t_vec3	ray_dir = {image_x, image_y, -1};
	ray_dir = normalize(ray_dir);
	return (ray_dir);
}


void	render_scene(t_graph *graph, t_scene *scene)
{
	int	x;
	int	y;
	t_vec3	ray_dir;
	//double	t;	//Variable para almacenar la distancia al objeto interceptado.
	//double	ambient = 0.1;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray_dir = compute_ray_dir(x, y , scene->cam);	//Calcular dirección del rayo desde la camara hasta el pixel actual.
			if (!handle_sphere_intersec(ray_dir, scene, x, y, graph)) // Verificar si el rayo intersecta con la esfera
			{
				if (!handle_plane_intersec(ray_dir, scene, x, y, graph))
					put_pixel_to_image(graph, x, y, BLACK);	//Si no hay intersección, fondo.
			}
			x++;
		}
		y++;
	}
}
