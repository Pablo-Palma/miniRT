/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:31:16 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/14 12:55:57 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	setup_gui(t_graph *graph)
{
	graph->mlx = mlx_init();
	if (!graph->mlx)
		return (EXIT_FAILURE);
	graph->win = mlx_new_window(graph->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	if (!graph->win)
		return (EXIT_FAILURE);
	init_img(graph);
	return (EXIT_SUCCESS);
}

void	init_img(t_graph *graph)
{
	graph->img = mlx_new_image(graph->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!graph->img)
	{
		ft_putstr_fd("Error: mlx_new_image failed\n", 2);
		exit(EXIT_FAILURE);
	}
	graph->addr = mlx_get_data_addr(graph->img, &(graph->bpp),
			&(graph->line_lenght), &(graph->endian));
}

int	cleanup(t_graph *graph)
{
	if (graph != NULL)
	{
		if (graph->img)
		{
			mlx_destroy_image(graph->mlx, graph->img);
			graph->img = NULL;
		}
		if (graph->win != NULL)
			graph->win = NULL;
	}
	exit(EXIT_SUCCESS);
	return (0);
}
