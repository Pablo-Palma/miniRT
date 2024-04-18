/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_method.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: math <math@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 21:49:17 by math              #+#    #+#             */
/*   Updated: 2024/04/19 00:33:03 by math             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	constructor(void *self)
{
	void	(*constructor)(void *);

	if (!ft_strncmp(((t_obj *)self)->line, "A", 1))
		constructor = a_light;
	else if (!ft_strncmp(((t_obj *)self)->line, "C", 1))
		constructor = camera;
	else if (!ft_strncmp(((t_obj *)self)->line, "L", 1))
		constructor = light;
	else if (!ft_strncmp(((t_obj *)self)->line, "sp", 2))
		constructor = sphere;
	else if (!ft_strncmp(((t_obj *)self)->line, "pl", 2))
		constructor = plane;
	else if (!ft_strncmp(((t_obj *)self)->line, "cy", 2))
		constructor = cylinder;
	else
		constructor = NULL;
	if (constructor)
		constructor(self);
}

void	intersect(t_obj *obj, t_ray *ray)
{
	int	ret;

	ret = 0;
	if (is_child(obj, "pl"))
		ret = intersect_pl(*(t_plane *)(obj->child), ray);
	else if (is_child(obj, "sp"))
		ret = intersect_sp(*(t_sphere *)(obj->child), ray);
	else if (is_child(obj, "cy"))
		ret = intersect_cyl((t_cyl *)(obj->child), ray);
	else if (is_child(obj, "L"))
		ret = intersect_light(*(t_light *)(obj->child), ray);
	else if (is_child(obj, "ci"))
		ret = intersect_circle(*(t_circle *)(obj->child), ray);
	if (ret)
	{
		*ray->obj = obj;
	}
}

int	check(t_obj *obj)
{
	int	ret;

	if (is_child(obj, "pl"))
		ret = check_pl((t_plane *)(obj->child));
	else if (is_child(obj, "sp"))
		ret = check_sp((t_sphere *)(obj->child));
	else if (is_child(obj, "cy"))
		ret = check_cyl((t_cyl *)(obj->child));
	else if (is_child(obj, "L"))
		ret = check_light((t_light *)(obj->child));
	else if (is_child(obj, "A"))
		ret = check_a_light((t_ambient_light *)(obj->child));
	else if (is_child(obj, "C"))
		ret = check_cam((t_cam *)(obj->child));
	else
		ret = EXIT_FAILURE;
	if (ret == EXIT_FAILURE)
		ft_putstr_fd(obj->line, 2);
	else if (ret == 2)
	{
		ft_putstr_fd(obj->line, 2);
		return (EXIT_SUCCESS);
	}
	return (ret);
}

t_vec3	get_normal(t_obj *obj, t_vec3 point)
{
	if (is_child(obj, "pl"))
		return (normal_pl((t_plane *)obj->child, point));
	else if (is_child(obj, "sp"))
		return (normal_sp((t_sphere *)obj->child, point));
	else if (is_child(obj, "cy"))
		return (normal_cyl((t_cyl *)obj->child, point));
	else
		return (point);
}
