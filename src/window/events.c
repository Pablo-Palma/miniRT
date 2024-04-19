/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:19:33 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/19 10:10:31 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	update_cam_pos(t_cam *cam, int keycode)
{
	double	move_step;

	move_step = 0.5;
	if (keycode == KEY_UP)
		cam->view_point.y += move_step;
	else if (keycode == KEY_DOWN)
		cam->view_point.y -= move_step;
	else if (keycode == KEY_W)
		cam->view_point.z -= move_step;
	else if (keycode == KEY_S)
		cam->view_point.z += move_step;
	else if (keycode == KEY_A)
		cam->orientation.x -= move_step;
	else if (keycode == KEY_D)
		cam->orientation.x += move_step;
	cam->orientation = normalize(cam->orientation);
}

int	handle_keyboard(int keycode, t_graph *graph, t_list *obj_list)
{
	t_list	*cur;
	t_obj	*obj;
	t_cam	*cam;

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
	update_cam_pos(cam, keycode);
	render_scene(graph, obj_list);
	mlx_put_image_to_window(graph->mlx, graph->win, graph->img, 0, 0);
	return (0);
}

int	handle_close(void *param)
{
	t_graph	*graph;

	graph = (t_graph *)param;
	cleanup(graph);
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
		handle_keyboard(keycode, graph, graph->obj_list);
	return (0);
}

void	setup_hooks(t_graph *graph)
{
	mlx_hook(graph->win, 2, 1L << 0, handle_key_press, graph);
	mlx_hook(graph->win, 17, 0L, handle_close, graph);
}
