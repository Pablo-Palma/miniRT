/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:19:33 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/18 12:24:12 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	handle_keyboard(int keycode, t_graph *graph, t_scene *scene)
{
	double	move_step;

	move_step = 0.5;
	if (keycode == KEY_UP)
		scene->cam.view_point.y += move_step;
	else if (keycode == KEY_DOWN)
		scene->cam.view_point.y -= move_step;
	else if (keycode == KEY_LEFT)
		scene->cam.view_point.x -= move_step;
	else if (keycode == KEY_RIGHT)
		scene->cam.view_point.x += move_step;
	else if (keycode == KEY_W)
		scene->cam.view_point.z -= move_step;
	else if (keycode == KEY_S)
		scene->cam.view_point.z += move_step;
	else if (keycode == KEY_A)
		scene->cam.orientation.z *= -1;
	render_scene(graph, scene);
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
		handle_keyboard(keycode, graph, graph->scene);
	return (0);
}

void	setup_hooks(t_graph *graph)
{
	mlx_hook(graph->win, 2, 1L << 0, handle_key_press, graph);
	mlx_hook(graph->win, 17, 0L, handle_close, graph);
}
