/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_constructor.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:17:56 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/18 22:29:19 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	a_light(void *parent)
{
	t_ambient_light	*self;
	char			**str;

	self = (t_ambient_light *)malloc(sizeof(t_ambient_light));
	str = nsplit(((t_obj *)parent)->line, ' ', 3);
	if (self && str && !constructor_color(&self->color, str[2]))
	{
		self->intensity = ft_atof(str[1]);
		((t_obj *)parent)->child = self;
		*((t_obj *)parent)->color = self->color;
	}
	else
		onfail_clean(((t_obj *)parent)->line, self);
	dbfree(str);
}

void	camera(void *parent)
{
	t_cam	*self;
	char	**str;

	self = (t_cam *)malloc(sizeof(t_cam));
	((t_obj *)parent)->child = self;
	str = nsplit(((t_obj *)parent)->line, ' ', 4);
	if (self && str && !constructor_vec(&self->view_point, str[1]) && !constructor_vec(&self->orientation, str[2]))
	{
		self->fov = ft_atoi(str[3]);
		*((t_obj *)parent)->origin = &self->view_point;
	}
	else
		onfail_clean(((t_obj *)parent)->line, self);
	dbfree(str);
}

void	light(void *parent)
{
	t_light		*self;
	char		**str;

	self = (t_light *)malloc(sizeof(t_light));
	((t_obj *)parent)->child = self;
	str = nsplit(((t_obj *)parent)->line, ' ', 4);
	if (self && str && !constructor_vec(&self->pos, str[1]) && !constructor_color(&self->color, str[3]))
	{
		self->brigthness = ft_atof(str[2]);
		*((t_obj *)parent)->origin = &self->pos;
		*((t_obj *)parent)->color = self->color;
	}
	else
		onfail_clean(((t_obj *)parent)->line, self);
	dbfree(str);
}

void	sphere(void *parent)
{
	t_sphere	*self;
	char		**str;

	self = (t_sphere *)malloc(sizeof(t_sphere));
	((t_obj *)parent)->child = self;
	str = nsplit(((t_obj *)parent)->line, ' ', 4);
	if (self && str && !constructor_vec(&self->center, str[1]) && !constructor_color(&self->color, str[3]))
	{
		self->radius = ft_atof(str[2]) / 2;
		*((t_obj *)parent)->origin = &self->center;
		*((t_obj *)parent)->color = self->color;
	}
	else
		onfail_clean(((t_obj *)parent)->line, self);
	dbfree(str);
}

void	plane(void *parent)
{
	t_plane	*self;
	char	**str;

	self = (t_plane *)malloc(sizeof(t_plane));
	((t_obj *)parent)->child = self;
	str = nsplit(((t_obj *)parent)->line, ' ', 4);
	if (self && str && !constructor_vec(&self->point, str[1]) && !constructor_vec(&self->normal, str[2]) && !constructor_color(&self->color, str[3]))
	{
		*((t_obj *)parent)->origin = &self->point;
		*((t_obj *)parent)->color = self->color;
	}
	else
		onfail_clean(((t_obj *)parent)->line, self);
	dbfree(str);
}
