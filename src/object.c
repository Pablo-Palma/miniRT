/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:21:29 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/19 03:53:26 by math             ###   ########.fr       */
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
	t_list	*cur;

	if (!obj)
		return (NULL);
	cur = obj;
	while (cur)
	{
		if (!ft_strncmp(((t_obj *)(cur->content))->line, str, ft_strlen(str)))
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}

int	obj_next(t_list **obj_ptr, char *str)
{
	if (!(*obj_ptr && (*obj_ptr)->next))
		return (0);
	*obj_ptr = (*obj_ptr)->next;
	while (*obj_ptr)
	{
		if (!ft_strncmp(((t_obj *)((*obj_ptr)->content))->line, str, ft_strlen(str)))
			return (1);
		*obj_ptr = (*obj_ptr)->next;
	}
	return (0);
}


t_list *get_objects(int fd)
{
	t_list	*obj;
	char	*line;
	char	*line_cam;
	char	*line_ambient_light;

	obj = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (*line == 'A')
			line_ambient_light = line;
		else if (*line == 'C')
			line_cam = line;
		else if (*line == 'L')
			ft_lstadd_back(&obj, ft_lstnew(new_obj((t_obj){line, NULL})));
		else
			ft_lstadd_front(&obj, ft_lstnew(new_obj((t_obj){line, NULL})));
		line = get_next_line(fd);
	}
	ft_lstadd_back(&obj, ft_lstnew(new_obj((t_obj){line_ambient_light, NULL})));
	ft_lstadd_back(&obj, ft_lstnew(new_obj((t_obj){line_cam, NULL})));
	close(fd);
	ft_lstiter(obj, constructor);
	ft_lstiter(obj, print_obj);
	return (obj);
}
