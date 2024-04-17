/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:26:25 by pabpalma          #+#    #+#             */
/*   Updated: 2024/04/17 18:47:30 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int check_all_obj(t_list *obj_list)
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
	ft_lstiter(graph->obj_list, print_obj);
	return (EXIT_SUCCESS);
}