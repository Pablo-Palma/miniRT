/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:30:33 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/17 17:41:24 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/miniRT.h"

int	main(int argc, char **argv)
{
	t_graph	graph;
	t_list	*obj;
	int		fd;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return(perror("open"), 1);
	obj = get_objects(fd);
	if (setup_gui(&graph) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	render_scene(&graph, obj);
	mlx_put_image_to_window(graph.mlx, graph.win, graph.img, 0, 0);
	setup_hooks(&graph);
	mlx_loop(graph.mlx);
	return (EXIT_SUCCESS);
}
