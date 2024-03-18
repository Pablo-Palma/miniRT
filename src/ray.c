/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 06:28:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/18 16:37:10 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_ray	*new_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray *self;

	self = (t_ray *)malloc(sizeof(t_ray));
	if (!self)
		return (NULL);
	self->origin = origin;
	self->direction = (normalize(direction));
	self->obj = (t_list **)malloc(sizeof(t_list *));
	*(self->obj) = NULL;
	self->t = 10000000;
	self->next = NULL;
	return (self);
}

void	delete_ray(void *param)
{
	t_ray	*self;

	if (!param)
		return;
	self = (t_ray *)param;
	if (self->next)
		ft_lstclear(&self->next, delete_ray);
	free(self->obj);
	free(self);
}

void	ray_trace_light(t_ray *ray)
{
	t_vec3	origin;
	t_vec3	direction;
	t_list	**light;

	if (!(ray && *ray->obj))
		return ;
	print_obj(ray->obj);
	light = ray->obj;
	while (obj_next(light, "A"))
	{
		origin = (t_vec3){ray->direction.x * ray->t, ray->direction.y * ray->t, ray->direction.z * ray->t};
		direction = vector_sub(origin, ((t_light *)((t_obj *)(*light)->content)->child)->pos);
		ft_lstadd_back(&(ray->next), ft_lstnew(new_ray(origin, direction)));
		*((t_ray *)ft_lstlast(ray->next)->content)->obj = *light;
		((t_ray *)ft_lstlast(ray->next)->content)->t = vector_length(direction);
	}
}