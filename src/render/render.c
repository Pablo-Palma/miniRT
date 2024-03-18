/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/18 16:42:01 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

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
	return (ray_dir);
}

void	render_scene(t_graph *graph, t_list *obj)
{
	t_ambient_light	ambient_light;
	t_cam			cam;
	t_list			*cur;
	t_list			*ray = NULL;
	int				x;
	int				y;
	int				ambient_color;

	if (objchr(obj, "A"))
		ambient_light = *(t_ambient_light *)((t_obj *)objchr(obj, "A")->content)->child;
	cam = *(t_cam *)((t_obj *)objchr(obj, "C")->content)->child;

	// t_light	light = *(t_light *)((t_obj *)objchr(obj, "L")->content)->child;
	//double	t;	//Variable para almacenar la distancia al objeto interceptado.
	//double	ambient = 0.1;

	printf("%f\n", ambient_light.intensity);
	printf("%d\n", ambient_light.color);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			ft_lstadd_back(&ray, ft_lstnew((void *)new_ray(cam.orientation, compute_ray_dir(x, y , cam))));
			cur = obj;
			while (cur)
			{
				intersect(cur, (t_ray *)ray->content); //saves first intersection with and obj and set ray.t
				cur = cur->next;
			}
			ft_lstadd_back(&ray, ft_lstnew((void *)new_ray(((t_ray *)ray->content)->origin, ((t_ray *)ray->content)->direction)));
			//int	color = trace_light(obj, (t_ray *)ft_lstlast(ray)->content);
			if (*((t_ray *)ray->content)->obj)
			{
				ray_trace_light((t_ray *)ray->content);
				put_pixel_to_image(graph, x, y, CIAN);
			}
			else
			{
				ambient_color = mix_colors(ambient_light, ambient_light.color, ambient_light.intensity, 0.0);
				put_pixel_to_image(graph, x, y, ambient_color);
			}
			ft_lstclear(&ray, delete_ray);
		}
	}
}
