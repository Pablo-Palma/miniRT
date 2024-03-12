/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabpalma <pabpalma>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:30:33 by pabpalma          #+#    #+#             */
/*   Updated: 2024/03/12 16:53:14 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	main(int argc, char **argv)
{
	t_graph	graph;
	t_scene	scene;

	(void)argc;
	if (setup_gui(&graph) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!parse_file(argv[1], &scene))
	{
		ft_putstr_fd("Failed to parse the scene file.\n", 2);
		return (EXIT_FAILURE);
	}
	init_scene(&scene);
	render_scene(&graph, &scene);
	mlx_put_image_to_window(graph.mlx, graph.win, graph.img, 0, 0);
	setup_hooks(&graph);
	mlx_loop(graph.mlx);
	return (EXIT_SUCCESS);
}
