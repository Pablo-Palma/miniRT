/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:19:33 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/03 13:23:17 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

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
	return (0);
}

void	setup_hooks(t_graph *graph)
{
	mlx_hook(graph->win, 2, 1L << 0, handle_key_press, graph);
	mlx_hook(graph->win, 17, 0L, handle_close, graph);
}
