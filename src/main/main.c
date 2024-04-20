/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:30:33 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/20 09:13:34 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_extension(char *file)
{
	char	*extension;

	extension = ft_strrchr(file, '.');
	if (!extension || ft_strncmp(extension, ".rt", 4))
	{
		ft_putstr_fd("miniRT: not an rt file\n", 2);
		return (0);
	}
	return (1);
}

int	open_rt_file(char *file)
{
	int	fd;

	if (open(file, O_DIRECTORY) > 0)
	{
		ft_putstr_fd("miniRT: erro is a directory\n", 2);
		return (-1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (perror("open"), -1);
	if (!is_extension(file))
		return (-1);
	return (fd);
}

int	main(int argc, char **argv)
{
	t_graph	graph;
	int		fd;

	if (argc != 2)
		return (ft_putstr_fd("miniRT: Wrong number of arguments\n"
				, 2), EXIT_FAILURE);
	fd = open_rt_file(argv[1]);
	if (fd == -1)
		return (EXIT_FAILURE);
	if (parse(&graph, fd))
		return (EXIT_FAILURE);
	if (setup_gui(&graph) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	render_scene(&graph, graph.obj_list);
	mlx_put_image_to_window(graph.mlx, graph.win, graph.img, 0, 0);
	setup_hooks(&graph);
	mlx_loop(graph.mlx);
	return (EXIT_SUCCESS);
}
