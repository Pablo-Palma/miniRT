/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:26:25 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/19 16:20:16 by pabpalma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	scene_count_obj(t_list *obj_list, char *id)
{
	t_list	*cur;
	int		count;

	count = 0;
	cur = obj_list;
	while (cur)
	{
		if (is_child(cur->content, id))
			count++;
		cur = cur->next;
	}
	return (count);
}

int	check_scene(t_list *obj_list)
{
	if (scene_count_obj(obj_list, "C") != 1)
	{
		if (scene_count_obj(obj_list, "C") < 1)
			ft_putstr_fd("miniRT: No camera found\n", 2);
		else
			ft_putstr_fd("miniRT: Many cameras\n", 2);
		return (EXIT_FAILURE);
	}
	if (scene_count_obj(obj_list, "A") != 1)
	{
		if (scene_count_obj(obj_list, "A") < 1)
			ft_putstr_fd("miniRT: No ambient light set\n", 2);
		else
			ft_putstr_fd("miniRT: Many ambient lights\n", 2);
		return (EXIT_FAILURE);
	}
	if (scene_count_obj(obj_list, "L") != 1)
	{
		if (scene_count_obj(obj_list, "L") < 1)
			ft_putstr_fd("miniRT: No light found\n", 2);
		else
			return (ft_putstr_fd("miniRT: Many lights\n", 2), EXIT_SUCCESS);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	check_all_obj(t_list *obj_list)
{
	t_list	*cur;

	cur = obj_list;
	while (cur)
	{
		if (check((t_obj *)cur->content))
			return (EXIT_FAILURE);
		cur = cur->next;
	}
	return (EXIT_SUCCESS);
}

int	parse(t_graph *graph, int fd)
{
	graph->obj_list = get_objects(fd);
	if (check_all_obj(graph->obj_list))
		return (EXIT_FAILURE);
	if (check_scene(graph->obj_list))
		return (EXIT_FAILURE);
	ft_lstiter(graph->obj_list, print_obj);
	return (EXIT_SUCCESS);
}

void	onfail_clean(char *line, void *self)
{
	ft_putstr_fd("\tline: ", 2);
	ft_putstr_fd(ft_strtrim(line, "\n"), 2);
	ft_putstr_fd("\n", 2);
	if (self)
		free(self);
	self = NULL;
}
