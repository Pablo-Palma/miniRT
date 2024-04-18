/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_method2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 22:31:43 by math              #+#    #+#             */
/*   Updated: 2024/04/18 23:26:01 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	checkerboard(t_obj *obj, t_vec3 point)
{
	int	ret;

	if (is_child(obj, "pl"))
		ret = checkerboard_pl(point);
	else if (is_child(obj, "sp"))
		ret = checkerboard_sp(*(t_sphere *)(obj->child), point);
	else if (is_child(obj, "cy"))
		ret = checkerboard_cyl(*(t_cyl *)(obj->child), point);
	else
		ret = 0;
	if (ret)
	{
		return (ret);
	}
	return (0);
}

void	print_obj(void *self)
{
	if (is_child((t_obj *)self, "A"))
		print_a_light(((t_obj *)self)->child);
	else if (is_child((t_obj *)self, "C"))
		print_camera(((t_obj *)self)->child);
	else if (is_child((t_obj *)self, "L"))
		print_light(((t_obj *)self)->child);
	else if (is_child((t_obj *)self, "sp"))
		print_sphere(((t_obj *)self)->child);
	else if (is_child((t_obj *)self, "pl"))
		print_plane(((t_obj *)self)->child);
	else if (is_child((t_obj *)self, "cy"))
		print_cylinder(((t_obj *)self)->child);
}
