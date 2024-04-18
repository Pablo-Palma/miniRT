/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_constructor2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:28:57 by math              #+#    #+#             */
/*   Updated: 2024/04/18 22:33:37 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	cylinder(void *parent)
{
	t_cyl	*self;
	char	**str;

	self = (t_cyl *)malloc(sizeof(t_cyl));
	((t_obj *)parent)->child = self;
	str = nsplit(((t_obj *)parent)->line, ' ', 6);
	if (self && str && !constructor_vec(&self->center, str[1])
		&& !constructor_vec(&self->dir, str[2])
		&& !constructor_color(&self->color, str[5]))
	{
		self->radius = ft_atof(str[3]) / 2;
		self->h = ft_atof(str[4]);
		*((t_obj *)parent)->origin = &self->center;
		*((t_obj *)parent)->color = self->color;
	}
	else
		onfail_clean(((t_obj *)parent)->line, self);
	dbfree(str);
}
