/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:21:29 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/13 05:10:38 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

static void	constructor(void *self)
{
	void	(*constructor)(void *);
	
	if (!ft_strncmp(((t_obj *)self)->line, "A", 1)) //ambient light
		constructor = a_light;
	else if (!ft_strncmp(((t_obj *)self)->line, "C", 1)) //camera
		constructor = camera;
	else if (!ft_strncmp(((t_obj *)self)->line, "L", 1)) //light
		constructor = light;
	else if (!ft_strncmp(((t_obj *)self)->line, "sp", 2)) //sphere
		constructor = sphere;
	else if (!ft_strncmp(((t_obj *)self)->line, "pl", 2)) //plane
		constructor = plane;
	else if (!ft_strncmp(((t_obj *)self)->line, "cy", 2)) //cylinder
		constructor = cylinder;
	else
		constructor = NULL; // Handle unrecognized object types
	if (constructor)
		constructor(self);
}

static t_obj	*new_obj(t_obj obj)
{
	t_obj	*self;

	self = (t_obj *)malloc(sizeof(t_obj));
	*self = obj;
	return (self);
}

t_list	*objchr(t_list *obj, char *str)
{
	while (obj)
	{
		if (!ft_strncmp(((t_obj *)(obj->content))->line, str, ft_strlen(str)))
			return (obj);
		obj = obj->next;
	}
	return (NULL);
}

t_list *get_objects(int fd)
{
	t_list	*obj;
	char	*line;

	obj = NULL;
	line = get_next_line(fd);
	while (line)
	{
		ft_lstadd_back(&obj, ft_lstnew(new_obj((t_obj){line, NULL})));
		line = get_next_line(fd);
	}
	close(fd);
	ft_lstiter(obj, constructor);
	ft_lstiter(obj, print_obj);
	return (obj);
}
