/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/25 18:04:13 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

t_vec3 compute_ray_dir(int x, int y, t_cam cam)
{
    double fov_rad = cam.fov * M_PI / 180.0;
    double aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT;
    double scale = tan(fov_rad / 2.0);
    double image_x = (2 * (x + 0.5) / (double)WIN_WIDTH - 1) * aspect_ratio * scale;
    double image_y = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT) * scale;
    t_vec3 ray_dir = cam.orientation;
    ray_dir.x += image_x;
    ray_dir.y += image_y;
    return ray_dir;
}

// {
// 	double	fov_rad = cam.fov * M_PI / 180.0;	//Lo convertimo a Radianes para poder utilizar funciones trigonométricas.
// 	// (para converir a radian = alguno del campo de vision * pi / 180)
// 	double	aspect_ratio = (double)WIN_WIDTH / (double)WIN_HEIGHT; //relacción aspecto, (ancho venta / alto ventana), MANTENER ESCALA.
// 	double	scale = tan(fov_rad / 2.0);	//tamaño de imagen a escala
// 	//CALCULAR LAS CORDENADAS EN EL ESPACIO DE LA IMAGEN-----
// 	double	image_x = (2 * (x + 0.5) / (double)WIN_WIDTH - 1) * aspect_ratio * scale; //multiplicarlo mantiene la proporcion.
// 	double	image_y = (1 - 2 * (y + 0.5) / (double)WIN_HEIGHT) * scale;	//	La altura del plano se deremina por la escala(vinculada al fov)
// 	//-----------
// 	//**	Construcción dirección del rayo, z en -1 por la dirección.
// 	t_vec3	ray_dir = {image_x, image_y, -1};
// 	return (ray_dir);
// }

void	render_scene(t_graph *graph, t_list *obj_list)
{
	t_ambient_light	ambient_light;
	t_cam			cam;
	t_list			*cur;
	t_list			**ray_list = (t_list **)malloc(sizeof(t_list *));
	t_list			*cur_ray = NULL;
	t_pixel			pixel;
	int				ambient_color;

	*ray_list = NULL;
	ambient_light = *(t_ambient_light *)((t_obj *)objchr(obj_list, "A")->content)->child;
	cam = *(t_cam *)((t_obj *)objchr(obj_list, "C")->content)->child;
	pixel = (t_pixel){-1,-1,0,0,0};
	while (++pixel.y < WIN_HEIGHT)
	{
		pixel = (t_pixel){pixel.y,-1,0,0,0};
		while (++pixel.x < WIN_WIDTH)
		{
			//TRACING RAY CAM TO OBJ
			ft_lstadd_back(ray_list, ft_lstnew((void *)new_ray(cam.view_point, compute_ray_dir(pixel.x, pixel.y , cam))));
			cur = obj_list;
			while (cur)
			{
				intersect(cur->content, (t_ray *)(*ray_list)->content);
				cur = cur->next;
			}
			if (!*((t_ray *)(*ray_list)->content)->obj) // FIRST RAY REACH VOID
			{
				ambient_color = mix_colors(ambient_light, ambient_light.color, ambient_light.intensity, 0.0);
				put_pixel_to_image(graph, pixel.x, pixel.y, ambient_color);
				ft_lstclear(ray_list, delete_ray);
				continue ;
			}
			//TRACING TO LIGHTS
			ray_trace_light((*ray_list)->content, obj_list); //initializate one ray.content.next (which is a t_list **), to each L, with its direction
			cur_ray = *((t_ray *)((*ray_list)->content))->next;
			while (cur_ray)
			{
				cur = obj_list;
				while (cur) // && to avoid self intersection
				{
					if (cur->content != *((t_ray *)(*ray_list)->content)->obj)
						intersect(cur->content, (t_ray *)cur_ray->content); //trace each cur_ray to obj or light && set cur_ray.obj and cur_ray.t
					cur = cur->next;
				}
				cur_ray = cur_ray->next;
			}
			//TRACING IMAGE
				//empty

			// COMPUTING RAY
			cur_ray = *((t_ray *)((*ray_list)->content))->next;
			if (*((t_ray *)cur_ray->content)->obj)
			{
				if (is_child(*((t_ray *)(cur_ray->content))->obj, "L"))
				{
					ray_sum((*ray_list)->content, &pixel, ambient_light);
					put_pixel_to_image(graph, pixel.x, pixel.y, pixel.color);
				}
				else //intersect other obj
				{
					ray_sum((*ray_list)->content, &pixel, ambient_light);
					put_pixel_to_image(graph, pixel.x, pixel.y, BLACK);
				}
			}
			else //intersect void
			{
				ray_sum((*ray_list)->content, &pixel, ambient_light);
				put_pixel_to_image(graph, pixel.x, pixel.y, pixel.color);
			}
			// // CLEANING
			ft_lstclear(ray_list, delete_ray);
		}
	}
}
