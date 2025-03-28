/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 18:14:03 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/20 09:58:17 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ray_start(t_list *obj_list, t_list **pool, t_ray *ray)
{
	t_list	*cur;
	t_list	*cur_ray;

	cur = NULL;
	cur_ray = NULL;
	ray_trace_light(ray, obj_list, pool);
	ray_trace_img(ray, pool);
	cur_ray = *(ray)->next;
	while (cur_ray)
	{
		cur = obj_list;
		while (cur)
		{
			if (cur->content != *(ray)->obj)
				intersect(cur->content, (t_ray *)cur_ray->content);
			cur = cur->next;
		}
		if (*((t_ray *)cur_ray->content)->obj)
		{
			if (!is_child(*((t_ray *)cur_ray->content)->obj, "L"))
				ray_start(obj_list, pool, cur_ray->content);
		}
		cur_ray = cur_ray->next;
	}
}

static void	first_intersect(t_list *obj_list, t_list **ray_list)
{
	t_list			*cur;

	cur = NULL;
	cur = obj_list;
	while (cur)
	{
		intersect(cur->content, (t_ray *)(*ray_list)->content);
		cur = cur->next;
	}
}

static int	raytracing(t_list *obj_list, t_list **pool,
		t_ray ray_dir, t_ambient_light *alight)
{
	t_list			**ray_list;
	t_list			*cur_ray;
	int				color;

	ray_list = lst_create();
	ft_lstadd_back(ray_list, lst_getpool_node(pool, ray_new,
			ray_cpy, &ray_dir));
	first_intersect(obj_list, ray_list);
	color = BLACK;
	if (*((t_ray *)(*ray_list)->content)->obj
		&& is_child(*((t_ray *)(*ray_list)->content)->obj, "L"))
		color = *(((t_obj *)(*((t_ray *)(*ray_list)->content)->obj))->color);
	else if (*((t_ray *)(*ray_list)->content)->obj)
	{
		cur_ray = NULL;
		ray_start(obj_list, pool, (*ray_list)->content);
		cur_ray = *((t_ray *)((*ray_list)->content))->next;
		if (*((t_ray *)cur_ray->content)->obj)
			color = vec_to_color(ray_sum((*ray_list)->content,
						vector_scale(color_to_vec((*alight).color),
							(*alight).intensity)));
	}
	ray_mv_to_pool(pool, ray_list);
	return (color);
}

void	render_scene(t_graph *graph, t_list *obj_list)
{
	t_ambient_light	*alight;
	t_list			**pool;
	t_pixel			pixel;
	t_cam			cam;
	t_ray			temp;

	alight = (t_ambient_light *)((t_obj *)objchr(obj_list,
				"A")->content)->child;
	pool = lst_create();
	cam = *(t_cam *)((t_obj *)objchr(obj_list, "C")->content)->child;
	pixel = (t_pixel){-1, -1};
	while (++pixel.y < WIN_HEIGHT)
	{
		pixel = (t_pixel){pixel.y, -1};
		while (++pixel.x < WIN_WIDTH)
		{
			temp.origin = cam.view_point;
			temp.direction = compute_ray_dir(pixel.x, pixel.y, cam);
			put_pixel_to_image(graph, pixel.x, pixel.y,
				raytracing(graph->obj_list, pool, temp, alight));
		}
	}
	ft_lstclear(pool, ray_delete);
}
