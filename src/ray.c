/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamagalh@student.42madrid.com <mamagalh    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 06:28:26 by mamagalh@st       #+#    #+#             */
/*   Updated: 2024/03/15 11:11:18 by mamagalh@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"

t_ray	*new_ray(t_vec3 origin, t_vec3 direction)
{
	t_ray *self;

	self = malloc(sizeof(t_ray));
	self->origin = origin;
	self->direction = (normalize(direction));
	self->obj = NULL;
	self->t = 10000000;
	return (self);
}