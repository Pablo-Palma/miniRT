/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 06:28:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/04/19 12:10:45 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray	ray_generic(t_vec3 origin, t_vec3 direction)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = direction;
	return (ray);
}

void	*ray_new(void *ray)
{
	t_ray	*self;

	self = (t_ray *)malloc(sizeof(t_ray));
	if (!self)
		return (NULL);
	self->obj = (t_obj **)malloc(sizeof(t_obj *));
	self->next = (t_list **)malloc(sizeof(t_list *));
	self->origin = ((t_ray *)ray)->origin;
	self->direction = ((t_ray *)ray)->direction;
	self->t = INFINITY;
	*self->obj = NULL;
	*self->next = NULL;
	self->reflect_level = 0;
	self->img_trace = 0;
	return ((void *)self);
}

void	ray_clean(void *node)
{
	t_ray	*self;

	self = (t_ray *)((t_list *)node)->content;
	self->origin = (t_vec3){0, 0, 0};
	self->direction = (t_vec3){0, 0, 0};
	self->t = INFINITY;
	*(self->obj) = NULL;
	*self->next = NULL;
	self->reflect_level = 0;
	self->img_trace = 0;
}

void	ray_cpy(void *self, void *ray)
{
	((t_ray *)self)->origin = ((t_ray *)ray)->origin;
	((t_ray *)self)->direction = ((t_ray *)ray)->direction;
}

void	ray_delete(void *param)
{
	t_ray	*self;

	if (!param)
		return ;
	self = (t_ray *)param;
	if (self->next)
		ft_lstclear(self->next, ray_delete);
	free(self->obj);
	free(self->next);
	free(self);
}
