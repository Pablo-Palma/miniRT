/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:30:33 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/13 18:28:33 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	main(int argc, char **argv)
{
	t_graph	graph;
	t_scene	scene;
	t_list	*objs;
	int		fd;

	(void)argc;
	fd = open(argv[1], O_RDONLY);
	objs = get_objects(fd);
	if (setup_gui(&graph) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	init_scene(&scene, objs);
	render_scene(&graph, &scene);
	mlx_put_image_to_window(graph.mlx, graph.win, graph.img, 0, 0);
	setup_hooks(&graph);
	mlx_loop(graph.mlx);
	return (EXIT_SUCCESS);
}
