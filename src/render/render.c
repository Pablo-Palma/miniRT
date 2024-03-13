/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/13 17:48:59 by mamagalh@st      ###   ########.fr       */
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
	double	image_x = (2 * (x + 0.5) / (double)WIN_WIDTH - 1) * aspect_ratio * scale; //multiplicarlo mantiene la proporcion.
	double	image_y = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT) * scale;	//	La altura del plano se deremina por la escala(vinculada al fov)
	//-----------
	//**	Construcción dirección del rayo, z en -1 por la dirección.
	t_vec3	ray_dir = {image_x, image_y, -1};
	ray_dir = normalize(ray_dir);
	return (ray_dir);
}


void	render_scene(t_graph *graph, t_scene *scene)
{
	int		x;
	int		y;
	t_vec3	ray_dir;
	int		ambient_color;
	//double	t;	//Variable para almacenar la distancia al objeto interceptado.
	//double	ambient = 0.1;

	printf("%f\n", scene->ambient_light.intensity);
	printf("%d\n", scene->ambient_light.color);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			ray_dir = compute_ray_dir(x, y , scene->cam);	//Calcular dirección del rayo desde la camara hasta el pixel actual.
			if (!handle_sphere_intersec(ray_dir, scene, z, graph)) // Verificar si el rayo intersecta con la esfera
			{
				if (!handle_cyl_intersec(ray_dir, scene, x, y, graph))
				{
					if (!handle_plane_intersec(ray_dir, scene, x, y, graph))
					{
						ambient_color = mix_colors(scene->ambient_light.color, scene->ambient_light.intensity, 0.0, *scene);
						put_pixel_to_image(graph, x, y, ambient_color);	//Si no hay intersección, fondo.
					}
				}
			}
			x++;
		}
		y++;
	}
}
