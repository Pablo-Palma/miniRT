/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/31 15:42:49 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

void	ray_start(t_list *obj_list, t_list **pool, t_ray *ray)
{
	t_list			*cur = NULL;
	t_list			*cur_ray = NULL;

	//TRACING TO LIGHTS
	ray_trace_light(ray, obj_list, pool); //initializate one ray.content.next (which is a t_list **), to each L, with its direction
	//TRACING IMAGE
	ray_trace_img(ray, obj_list, pool);
	//INTERSECT
	cur_ray = *(ray)->next;
	while (cur_ray)
	{
		cur = obj_list;
		while (cur)
		{
			if (cur->content != *(ray)->obj) // && to avoid self intersection
				intersect(cur->content, (t_ray *)cur_ray->content); //trace each cur_ray to obj or light && set cur_ray.obj and cur_ray.t
			cur = cur->next;
		}
		if (*((t_ray *)cur_ray->content)->obj) //(!is_child(*((t_ray *)(*ray_list)->content)->obj, "L"))
		{
			if (!is_child(*((t_ray *)cur_ray->content)->obj, "L"))
			{
				ray_start(obj_list, pool, cur_ray->content);
				// if (((t_ray *)cur_ray->content)->t >= (INFINITY - 100))
				// 	ray_start(obj_list, pool, cur_ray->content);
			}
		}
		else
		{
			/*ray img goes to void ==> mv ray back to pool*/
			//lst_mv_one_to_pool(pool, cur_ray, ray_clean);
		}
		// 	ray_start(obj_list, pool, ((t_ray *)((*ray_list)->content))->next, *((t_ray *)(cur_ray->content)));
		cur_ray = cur_ray->next;
	}
}

void	render_scene(t_graph *graph, t_list *obj_list)
{
	t_list			**ray_list;
	t_list			**pool;
	t_list			*cur = NULL;
	t_list			*cur_ray = NULL;
	t_ray			temp;
	t_pixel			pixel;
	t_ambient_light	ambient_light;
	t_cam			cam;

	ray_list = lst_create();
	pool = lst_create();
	ambient_light = *(t_ambient_light *)((t_obj *)objchr(obj_list, "A")->content)->child;
	cam = *(t_cam *)((t_obj *)objchr(obj_list, "C")->content)->child;
	pixel = (t_pixel){-1,-1,0,0,0};
	while (++pixel.y < WIN_HEIGHT)
	{
		pixel = (t_pixel){pixel.y,-1,0,0,0};
		while (++pixel.x < WIN_WIDTH)
		{
			//TRACING RAY CAM TO OBJ
			temp.origin = cam.view_point;
			temp.direction = compute_ray_dir(pixel.x, pixel.y, cam);
			ft_lstadd_back(ray_list, lst_getpool_node(pool, ray_new, ray_cpy, &temp));
			cur = obj_list;
			while (cur)
			{
				intersect(cur->content, (t_ray *)(*ray_list)->content);
				cur = cur->next;
			}
			if (!*((t_ray *)(*ray_list)->content)->obj) // FIRST RAY REACH VOID
			{
				put_pixel_to_image(graph, pixel.x, pixel.y, BLACK);
				ray_mv_to_pool(pool, ray_list);
				continue ;
			}
			// TRACING
			ray_start(obj_list, pool, (*ray_list)->content);
			// COMPUTING RAY
			cur_ray = *((t_ray *)((*ray_list)->content))->next;
			if (*((t_ray *)cur_ray->content)->obj)
			{
				pixel.color = vec_to_color(vector_add(ray_sum((*ray_list)->content, &pixel), vector_scale(color_to_vec(ambient_light.color), ambient_light.intensity)));
				put_pixel_to_image(graph, pixel.x, pixel.y, pixel.color);
			}
			// // MOVING TO POOL
			ray_mv_to_pool(pool, ray_list);
		}
	}
	//CLEANING
	ft_lstclear(ray_list, ray_delete);
}
