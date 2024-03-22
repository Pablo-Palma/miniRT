/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:19:33 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/22 01:44:44 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	handle_close(void *param)
{
	t_graph	*graph;

	graph = (t_graph *)param;
	cleanup(graph);
	return (0);
}

int	handle_cam_movement(int keycode, t_graph *graph, t_list *obj_list)
{
	t_list	*cur;
	t_obj	*obj;
	t_cam	*cam;
	double	move_step;

	obj = NULL;
	cam = NULL;
	cur = obj_list;
	while (cur)
	{
		obj = (t_obj *)cur->content;
		if (is_child(obj, "C"))
			break ;
		cur = cur->next;
	}
	cam = (t_cam *)obj->child;
	move_step = 0.5;
	if (keycode == KEY_UP)
		cam->view_point.y += move_step;
	else if (keycode == KEY_DOWN)
		cam->view_point.y -= move_step;
	else if (keycode == KEY_LEFT)
		cam->view_point.x -= move_step;
	else if (keycode == KEY_RIGHT)
		cam->view_point.x += move_step;
	else if (keycode == KEY_W)
		cam->view_point.z -= move_step;
	else if (keycode == KEY_S)
		cam->view_point.z += move_step;
	else if (keycode == KEY_A)
		cam->orientation.z *= -1;
	render_scene(graph, obj_list);
	mlx_put_image_to_window(graph->mlx, graph->win, graph->img, 0, 0);
	return (0);
}

int	handle_key_press(int keycode, t_graph *graph)
{
	if (keycode == KEY_ESC)
	{
		cleanup(graph);
		exit(EXIT_SUCCESS);
	}
	else
		handle_cam_movement(keycode, graph, graph->obj_list);
	return (0);
}

void	setup_hooks(t_graph *graph, t_list *obj_list)
{
	mlx_hook(graph->win, 2, 1L << 0, handle_cam_movement, obj_list);
	mlx_hook(graph->win, 2, 1L << 0, handle_key_press, graph);
	mlx_hook(graph->win, 17, 0L, handle_close, graph);
}
